# Required until Python 3.10
# See https://docs.python.org/dev/whatsnew/3.7.html#pep-563-postponed-evaluation-of-annotations)
from __future__ import annotations

from typing import Optional, Union
from database import pool


class User(object):
    def __init__(self, *,
                 id: int,
                 username: str,
                 password: str,
                 **kwargs):
        self.id = id
        self.username = username
        self.password = password

    @classmethod
    async def create(cls, *,
                     username: str,
                     password: str,
                     **kwargs) -> cls:
        query = """ INSERT INTO users
                        (username, password)
                    VALUES
                        (%s, %s)
                    RETURNING *
                """
        params = [username, password]
        result = await pool.fetchone(query, *params)

        return cls(**dict(result))

    @classmethod
    async def find(cls, id: int) -> Optional[cls]:
        query = """ SELECT
                        *
                    FROM users
                    WHERE id=%s
                    LIMIT 1
                """
        params = [id]
        result = await pool.fetchone(query, *params)

        return None if result is None else cls(**dict(result))

    @classmethod
    async def find_username(cls, username: str) -> Optional[cls]:
        query = """ SELECT
                        *
                    FROM users
                    WHERE username=%s
                    LIMIT 1
                """
        params = [username]
        result = await pool.fetchone(query, *params)

        return None if result is None else cls(**dict(result))
