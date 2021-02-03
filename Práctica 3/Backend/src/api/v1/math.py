from sanic import Blueprint
from sanic.exceptions import InvalidUsage, NotFound
from sanic.response import json
from decorators import validate_json, authenticate
from database.models import Calculation, CalculationOp


math = Blueprint('math', url_prefix='/math')

@math.route('/history/<id:int>', methods=['GET', 'OPTIONS'])
# @authenticate
async def get(request, id):
    calc = await Calculation.find(id=id)

    if not calc:
        raise NotFound()
    
    return json({
        'id': calc.id,
        'op': calc.op.value,
        'op1': calc.op1,
        'op2': calc.op2,
        'result': calc.res
    })

@math.route('/add', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True},
    'op2': {'type': 'number', 'required': True}
})
async def add(request):
    op1 = request.json.get('op1')
    op2 = request.json.get('op2')
    
    result = op1 + op2
    calc = await Calculation.create(op=CalculationOp.SUM, op1=op1,
                                    op2=op2, res=result)

    return json({
        'id': calc.id,
        'result': result
    })


@math.route('/subtract', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True},
    'op2': {'type': 'number', 'required': True}
})
async def subtract(request):
    op1 = request.json.get('op1')
    op2 = request.json.get('op2')
    
    result = op1 - op2
    calc = await Calculation.create(op=CalculationOp.SUB, op1=op1,
                                    op2=op2, res=result)

    return json({
        'id': calc.id,
        'result': result
    })


@math.route('/multiply', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True},
    'op2': {'type': 'number', 'required': True}
})
async def multiply(request):
    op1 = request.json.get('op1')
    op2 = request.json.get('op2')
    
    result = op1 * op2
    calc = await Calculation.create(op=CalculationOp.MULT, op1=op1,
                                    op2=op2, res=result)

    return json({
        'id': calc.id,
        'result': result
    })


@math.route('/divide', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True},
    'op2': {'type': 'number', 'required': True, 'forbidden': [0]}
})
async def divide(request):
    op1 = request.json.get('op1')
    op2 = request.json.get('op2')
    
    result = op1 / op2
    calc = await Calculation.create(op=CalculationOp.DIV, op1=op1,
                                    op2=op2, res=result)

    return json({
        'id': calc.id,
        'result': result
    })


@math.route('/modulo', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True},
    'op2': {'type': 'number', 'required': True, 'forbidden': [0]}
})
async def modulo(request):
    op1 = request.json.get('op1')
    op2 = request.json.get('op2')

    result = op1 % op2
    calc = await Calculation.create(op=CalculationOp.MOD, op1=op1,
                                    op2=op2, res=result)

    return json({
        'id': calc.id,
        'result': result
    })


@math.route('/sqrt', methods=['POST', 'OPTIONS'])
@authenticate
@validate_json({
    'op1': {'type': 'number', 'required': True, 'min': 0},
})
async def sqrt(request):
    import math

    op1 = request.json.get('op1')
    
    result = math.sqrt(op1)
    calc = await Calculation.create(op=CalculationOp.SQRT, op1=op1, res=result)

    return json({
        'id': calc.id,
        'result': result
    })
