from flask import Flask, request
import time

app = Flask(__name__)

dict_list_data = {
    "time": [],
    "name": [],
    "value": []
}

@app.route('/',  methods=['GET'])
def home():
    return "Halo, Selamat datang di halaman utama!"

@app.route('/data',  methods=['GET'])
def get_data():
    
    return dict_list_data, 200

@app.route('/create',  methods=['POST'])
def post_data():
    data = request.json
    data['time'] = time.time()
    dict_list_data['time'].append(data['time'])
    dict_list_data['name'].append(data['name'])
    dict_list_data['value'].append(data['value'])
    
    return f"{data['name']} berhasil mengirimkan data {data['value']}", 201

if __name__ == '__main__':
    app.run(debug=True, port=8000, host="<ipv4 address>")