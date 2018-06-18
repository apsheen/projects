import notify2

# initialise the d-bus connection
notify2.init("Tweets")
 
# create Notification object
n = notify2.Notification(None, icon = "Test")
 
# set urgency level
n.set_urgency(notify2.URGENCY_NORMAL)
 
# set timeout for a notification
n.set_timeout(10000)

# show notification on screen
n.show()