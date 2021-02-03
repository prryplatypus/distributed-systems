""" This file contains all routes required to manage USER logins.
    Since they only contain user logins they are routes which only
    need to be accessed from VATSIM applications/domains, so we do
    not want to allow CORS requests in these routes.
"""
import argon2
import config
import jwt
from sanic import Blueprint
from sanic.exceptions import Unauthorized, InvalidUsage
from sanic.response import json, empty
from datetime import datetime, timedelta
from decorators import validate_json, authenticate
from database.models import User


auth = Blueprint('auth', url_prefix='/auth')


@auth.route('/login', methods=['POST', 'OPTIONS'])
@validate_json({
    'username': {'type': 'string', 'required': True},
    'password': {'type': 'string', 'required': True}
})
async def login(request):
    user = await User.find_username(request.json.get('username'))
    if user:
        try:
            pwd_hasher = argon2.PasswordHasher()
            pwd_hasher.verify(user.password, request.json.get('password'))
        except argon2.exceptions.VerifyMismatchError:
            raise Unauthorized("Invalid login credentials")

        now = datetime.utcnow()
        token = jwt.encode({
            'iat': now,
            'exp': now + timedelta(hours=1),
            'sub': user.id
            },
            config.RSA_PRIV_KEY,
            algorithm='RS256'
        )

        return json({
            'token': token.decode()
        })

    raise Unauthorized("Invalid login credentials")


@auth.route('/create', methods=['POST', 'OPTIONS'])
@validate_json({
    'username': {'type': 'string', 'required': True},
    'password': {'type': 'string', 'required': True},
    'password_check': {'type': 'string', 'required': True}
})
async def create(request):
    if (pwd := request.json.get('password')) != request.json.get('password_check'):
        raise InvalidUsage("Password mismatch")
    elif await User.find_username(request.json.get('username')):
        raise InvalidUsage("Username exists")

    pwd_hasher = argon2.PasswordHasher()
    pwd = pwd_hasher.hash(pwd)

    user = await User.create(
        username=request.json.get('username'),
        password=pwd
    )

    now = datetime.utcnow()
    token = jwt.encode({
        'iat': now,
        'exp': now + timedelta(hours=1),
        'sub': user.id
        },
        config.RSA_PRIV_KEY,
        algorithm='RS256'
    )

    return json({
        'token': token.decode()
    })
