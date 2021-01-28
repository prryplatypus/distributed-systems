# Required until Python 3.10
# See https://docs.python.org/dev/whatsnew/3.7.html#pep-563-postponed-evaluation-of-annotations)
from __future__ import annotations

from typing import Optional, Union
from database import pool
from enum import Enum, unique


@unique
class CalculationOp(Enum):
    SUM = '+'
    SUB = '-'
    DIV = '/'
    MULT = '*'
    MOD = '%'
    SQRT = '√'


class Calculation(object):
    def __init__(self, *,
                 id: int,
                 op: str,
                 op1: float,
                 op2: Optional[float] = None,
                 res: float,
                 **kwargs):
        self.id = id
        self.op = CalculationOp(op)
        self.op1 = op1
        self.op2 = op2
        self.res = res

    @classmethod
    async def create(cls, *,
                     op: CalculationOp,
                     op1: float,
                     op2: Optional[float] = None,
                     res: float,
                     **kwargs) -> cls:
        query = """ INSERT INTO calculations
                        (op, op1, op2, res)
                    VALUES
                        (%s, %s, %s, %s)
                    RETURNING *
                """
        params = [op.value, op1, op2, res]

        result = await pool.fetchone(query, *params)

        return cls(**dict(result))
