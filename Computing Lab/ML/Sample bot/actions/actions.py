# This files contains your custom actions which can be used to run
# custom Python code.
#
# See this guide on how to implement these action:
# https://rasa.com/docs/rasa/custom-actions


# This is a simple example for a custom action which utters "Hello World!"

# from typing import Any, Text, Dict, List
#
# from rasa_sdk import Action, Tracker
# from rasa_sdk.executor import CollectingDispatcher
#
#
# class ActionHelloWorld(Action):
#
#     def name(self) -> Text:
#         return "action_hello_world"
#
#     def run(self, dispatcher: CollectingDispatcher,
#             tracker: Tracker,
#             domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:
#
#         dispatcher.utter_message(text="Hello World!")
#
#         return []

from rasa_sdk import Action
from rasa_sdk.events import SlotSet

# class ActionStoreName(Action):
#     def name(self) -> str:
#         return "action_store_name"

#     def run(self, dispatcher, tracker, domain):
#         # Extract the name entity
#         user_name = next(tracker.get_latest_entity_values("name"), None)
#         if user_name:
#             return [SlotSet("user_name", user_name)]
#         return []


class ActionStoreBrand(Action):
    def name(self) -> str:
        return "action_store_brand"

    def run(self, dispatcher, tracker, domain):
        # Extract the brand entity
        car_brand = next(tracker.get_latest_entity_values("brand"), None)
        if car_brand:
            return [SlotSet("brand", car_brand)]
        return []

class ActionStoreModel(Action):
    def name(self) -> str:
        return "action_store_model"

    def run(self, dispatcher, tracker, domain):
        # Extract the model entity
        car_model = next(tracker.get_latest_entity_values("model"), None)
        if car_model:
            return [SlotSet("model", car_model)]
        return []

class ActionStoreYearOfManufacture(Action):
    def name(self) -> str:
        return "action_store_year_of_manufacture"

    def run(self, dispatcher, tracker, domain):
        # Extract the year_of_manufacture entity
        car_year = next(tracker.get_latest_entity_values("year_of_manufacture"), None)
        if car_year:
            return [SlotSet("year_of_manufacture", car_year)]
        return []

class ActionStoreKmDriven(Action):
    def name(self) -> str:
        return "action_store_km_driven"

    def run(self, dispatcher, tracker, domain):
        # Extract the km_driven entity
        car_km = next(tracker.get_latest_entity_values("km_driven"), None)
        if car_km:
            return [SlotSet("km_driven", car_km)]
        return []

class ActionStoreFuelType(Action):
    def name(self) -> str:
        return "action_store_fuel_type"

    def run(self, dispatcher, tracker, domain):
        # Extract the fuel_type entity
        car_fuel_type = next(tracker.get_latest_entity_values("fuel_type"), None)
        if car_fuel_type:
            return [SlotSet("fuel_type", car_fuel_type)]
        return []

class ActionStoreTransmissionType(Action):
    def name(self) -> str:
        return "action_store_transmission_type"

    def run(self, dispatcher, tracker, domain):
        # Extract the transmission_type entity
        car_transmission = next(tracker.get_latest_entity_values("transmission_type"), None)
        if car_transmission:
            return [SlotSet("transmission_type", car_transmission)]
        return []

class ActionStoreMileage(Action):
    def name(self) -> str:
        return "action_store_mileage"

    def run(self, dispatcher, tracker, domain):
        # Extract the mileage entity
        car_mileage = next(tracker.get_latest_entity_values("mileage"), None)
        if car_mileage:
            return [SlotSet("mileage", car_mileage)]
        return []

class ActionStoreEngine(Action):
    def name(self) -> str:
        return "action_store_engine"

    def run(self, dispatcher, tracker, domain):
        # Extract the engine entity
        car_engine = next(tracker.get_latest_entity_values("engine"), None)
        if car_engine:
            return [SlotSet("engine", car_engine)]
        return []

class ActionStoreMaxPower(Action):
    def name(self) -> str:
        return "action_store_max_power"

    def run(self, dispatcher, tracker, domain):
        # Extract the max_power entity
        car_max_power = next(tracker.get_latest_entity_values("max_power"), None)
        if car_max_power:
            return [SlotSet("max_power", car_max_power)]
        return []

class ActionStoreSeats(Action):
    def name(self) -> str:
        return "action_store_seats"

    def run(self, dispatcher, tracker, domain):
        # Extract the seats entity
        car_seats = next(tracker.get_latest_entity_values("seats"), None)
        if car_seats:
            return [SlotSet("seats", car_seats)]
        return []

class ActionDisplayCarDetails(Action):
    def name(self) -> str:
        return "action_display_car_details"

    def run(self, dispatcher, tracker, domain):
        # Retrieve all car details from the corresponding slots
        brand = tracker.get_slot("brand")
        model = tracker.get_slot("model")
        year_of_manufacture = tracker.get_slot("year_of_manufacture")
        km_driven = tracker.get_slot("km_driven")
        fuel_type = tracker.get_slot("fuel_type")
        transmission_type = tracker.get_slot("transmission_type")
        mileage = tracker.get_slot("mileage")
        engine = tracker.get_slot("engine")
        max_power = tracker.get_slot("max_power")
        seats = tracker.get_slot("seats")

        # Check if all slots have been filled
        if all([brand, model, year_of_manufacture, km_driven, fuel_type, transmission_type, mileage, engine, max_power, seats]):
            # Format a response message with all the car details
            car_details = (
                f"Here are the details of your car:\n"
                f"Brand: {brand}\n"
                f"Model: {model}\n"
                f"Year of Manufacture: {year_of_manufacture}\n"
                f"Kilometers Driven: {km_driven} km\n"
                f"Fuel Type: {fuel_type}\n"
                f"Transmission Type: {transmission_type}\n"
                f"Mileage: {mileage} km/l\n"
                f"Engine: {engine} cc\n"
                f"Max Power: {max_power} bhp\n"
                f"Seats: {seats}"
            )
            # Send the details back to the user
            dispatcher.utter_message(text=car_details)
        else:
            dispatcher.utter_message(text="Some car details are missing. Please provide complete information.")
        
        return []






# class ActionDisplayName(Action):
#     def name(self) -> str:
#         return "action_display_name"

#     def run(self, dispatcher, tracker, domain):
#         # Retrieve the user's name from the slot
#         user_name = tracker.get_slot("user_name")
#         if user_name:
#             # Send a message back to the user
#             dispatcher.utter_message(text=f"Your name is {user_name}.")
#         else:
#             dispatcher.utter_message(text="I don't have your name stored.")
#         return []

