import streamlit as st
import requests
import pandas as pd

# Define the base URL of your API
BASE_URL = "http://<ipv4 address>:8000"

# Define the API endpoints
GET_ENDPOINT = "/data"
POST_ENDPOINT = "/create"

# Define the API headers
headers = {
    "Content-Type": "application/json",
    "Authorization": "Bearer your_token_here"
}

# Define the API GET method
def get_data():
    response = requests.get(BASE_URL + GET_ENDPOINT)
    if response.status_code == 200:
        data = response.json()
        df = pd.DataFrame(data)

        df['time'] = pd.to_datetime(df['time'], unit='s')
        st.table(df)

        st.write("GET Request Successful!")
    else:
        st.write("GET Request Failed!")

# Define the API POST method
def post_data(payload):
    response = requests.post(BASE_URL + POST_ENDPOINT, json=payload)
    if response.status_code == 201:
        data = response.text
        st.write(data)
    else:
        st.write("POST Request Failed!")

# Main function
def main():
    st.title("API Demo")
    st.subheader("GET Request")
    if st.button("GET Data"):
        get_data()

    # st.subheader("POST Request")
    # payload = {
    #     "name": st.text_input("Siapa nama anda"),
    #     "barang": st.text_input("Masukkan barang yang ingin diinputkan")
    # }
    # if st.button("Submit"):
    #     post_data(payload)

if __name__ == "__main__":
    main()