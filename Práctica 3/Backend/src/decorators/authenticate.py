import jwt
import config
from functools import wraps
from sanic.exceptions import Unauthorized


def authenticate(func):
    @wraps(func)
    async def wrapper(request, *args, **kwargs):
        auth_hdr = request.headers.get('Authorization', None)
        if not auth_hdr:
            raise Unauthorized("Missing token")

        try:
            jwt.decode(auth_hdr, config.RSA_PUB_KEY,
                       leeway=60, algorithms=['RS256'])
        except Exception:
            raise Unauthorized("Invalid token")
        return await func(request, *args, **kwargs)
    return wrapper
