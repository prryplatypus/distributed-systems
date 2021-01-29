import api
from sanic import Sanic
from sanic_cors import CORS
from database import pool


class App(Sanic):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.cors = CORS(self, resources={
            r"/api/v1/*": {
                "origins": "*"
            }
        })
        self.blueprint(api.v1)
        self.register_listener(pool.create, 'before_server_start')
        self.register_listener(pool.close, 'after_server_stop')


if __name__ == '__main__':
    app = App(__name__)
    app.run(host='0.0.0.0', port=8000, access_log=False, debug=False)
