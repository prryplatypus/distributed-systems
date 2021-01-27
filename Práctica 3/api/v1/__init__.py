from sanic import Blueprint
from .auth import auth
from .math import math

v1 = Blueprint.group(
    auth,
    math,
    url_prefix="/api/v1"
)
