import aiomysql
import config


class Pool(object):
    def __init__(self):
        self.pool = None

    async def create(self, app, loop) -> None:
        self.pool = await aiomysql.create_pool(host=config.DB_HOST,
                                               db=config.DB_NAME,
                                               user=config.DB_USER,
                                               password=config.DB_PASS,
                                               cursorclass=aiomysql.cursors.DictCursor,
                                               echo=True)

    async def close(self, app, loop) -> None:
        self.pool.close()
        await self.pool.wait_closed()
        self.pool = None

    async def execute(self, query, *args, **kwargs):
        async with self.pool.acquire() as conn:
            async with conn.cursor() as cur:
                await cur.execute(query, args)
            await conn.commit()

    async def executemany(self, query, *args, **kwargs):
        async with self.pool.acquire() as conn:
            async with conn.cursor() as cur:
                await cur.executemany(query, list(args))
            await conn.commit()

    async def fetchone(self, query, *args, **kwargs):
        async with self.pool.acquire() as conn:
            async with conn.cursor() as cur:
                await cur.execute(query, args)
                row = await cur.fetchone()
            await conn.commit()
        return row

    async def fetchall(self, query, *args, **kwargs):
        async with self.pool.acquire() as conn:
            async with conn.cursor() as cur:
                await cur.execute(query, args)
                rows = await cur.fetchall()
            await conn.commit()
        return rows


pool = Pool()
