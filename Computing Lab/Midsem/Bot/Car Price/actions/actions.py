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

class ActionStoreBrand(Action):
    def name(self) -> str:
        return "action_store_brand"

    def run(self, dispatcher, tracker, domain):
        # Extract the brand entity
        car_brand = next(tracker.get_latest_entity_values("brand"), None)
        if car_brand:
            # Store the brand in the slot
            dispatcher.utter_message(text=f"The car brand {car_brand} has been successfully stored.")
            return [SlotSet("brand", car_brand)]
        else:
            dispatcher.utter_message(text="I couldn't store the car brand. Please try again.")
        return []


class ActionStoreModel(Action):
    def name(self) -> str:
        return "action_store_model"

    def run(self, dispatcher, tracker, domain):
        # Extract the model entity
        car_model = next(tracker.get_latest_entity_values("model"), None)
        if car_model:
            # Store the model in the slot
            dispatcher.utter_message(text=f"The car model {car_model} has been successfully stored.")
            return [SlotSet("model", car_model)]
        else:
            dispatcher.utter_message(text="I couldn't store the car model. Please try again.")
        return []



class ActionDisplayCarDetails(Action):
    def name(self) -> str:
        return "action_display_car_details"

    def run(self, dispatcher, tracker, domain):
        # Retrieve the brand and model from the slots
        brand = tracker.get_slot("brand")
        model = tracker.get_slot("model")

        # Construct a response based on the available information
        if brand and model:
            dispatcher.utter_message(text=f"The car brand is {brand} and the model is {model}.")
        elif brand:
            dispatcher.utter_message(text=f"The car brand is {brand}, but I don't have the model.")
        elif model:
            dispatcher.utter_message(text=f"The car model is {model}, but I don't have the brand.")
        else:
            dispatcher.utter_message(text="I don't have the car brand or model stored.")

        return []


