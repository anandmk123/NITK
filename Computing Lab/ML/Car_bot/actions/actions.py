import requests
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher

class ActionPredictCarPrice(Action):
    def name(self) -> str:
        return "action_predict_car_price"

    def run(self, dispatcher: CollectingDispatcher, tracker: Tracker, domain: dict) -> list:
        # Extract the required slot values
        brand = tracker.get_slot('brand')
        model = tracker.get_slot('model')
        year_of_manufacture = tracker.get_slot('year_of_manufacture')
        km_driven = tracker.get_slot('km_driven')
        fuel_type = tracker.get_slot('fuel_type')
        transmission_type = tracker.get_slot('transmission_type')
        mileage = tracker.get_slot('mileage')
        engine = tracker.get_slot('engine')
        max_power = tracker.get_slot('max_power')
        seats = tracker.get_slot('seats')

        # Construct the API URL
        api_url = f"http://127.0.0.1:5000/max_contribution?brand={brand}&model={model}&year_of_manufacture={year_of_manufacture}&km_driven={km_driven}&fuel_type={fuel_type}&transmission_type={transmission_type}&mileage={mileage}&engine={engine}&max_power={max_power}&seats={seats}"

        try:
            # Make a GET request to the API
            response = requests.get(api_url)
            response.raise_for_status()  # Raise an error for bad responses

            # Extract price from the response
            price_data = response.json()  # Assuming the API returns JSON
            price = price_data.get('price', 'Not available')  # Adjust key as necessary

            # Send the price back to the user
            dispatcher.utter_message(text=f"The predicted price of the car is: {price}")

        except requests.exceptions.RequestException as e:
            dispatcher.utter_message(text="Sorry, I couldn't fetch the price. Please try again later.")
            print(f"Error occurred: {e}")  # Log the error for debugging

        return []
