""" 
    Example of what this client may look like
"""

from usb_protocol import USB_Message, USB_MSGS

def spin_motors(thrusts: list[float]):
    usb_message = USB_Message()
    usb_message.topic_id = USB_MSGS.MOTOR_TOPIC_ID    
    usb_message.subtopic_id = USB_MSGS.NONE
    usb_message.flags = USB_MSGS.NO_SUBTOPIC
    usb_message.data = thrusts # you would actually have to do float to byte conversion here
