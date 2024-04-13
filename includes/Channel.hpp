
/* We need to implement thoses function :
    join(user): This method adds a User object to the users list, signifying the user has joined the channel. It can potentially broadcast a join message to other users in the channel.
    part(user): This method removes a User object from the users list when the user leaves the channel. It can potentially broadcast a part message to other users in the channel.
    send_message(message): This method takes a Message object and broadcasts the message content to all users in the users list.
    get_users(): This method returns a list of all usernames or User objects currently joined in the channel.
*/

#pragma once
#include <iostream>
#include <map>
#include "Client.hpp"

class Channel
{
private:
    /* data */
    std::string _name; //String representing the channel name (e.g., "#programming")
    std::string _topic; // String representing the current topic of the channel (optional)
    std::string _mode; // String representing the current channel mode (e.g., "+v" for voice mode)
    std::map<std::string, Client*> _memberLists; // List or set containing User objects currently joined in the channel
public:
    Channel();
    Channel(const std::string& name); // Constructor with channel name

    Channel(const Channel& copy); // // Copy constructor and assignment operator (implement proper copying of User objects in the map)

    Channel& operator=(const Channel& other);

    // void join(User* user); // Add a user to the channel

    // void part(User* user); // Remove a user from the channel

    // Set the channel name (consider security implications)
    void setName(const std::string& name);

    // Get the channel name
    const std::string& getName() const;

    // Set the channel topic
  void setTopic(const std::string& topic);

    // Get the channel topic
  const std::string& getTopic() const;

  // Set the channel mode
  void setMode(const std::string& mode);

  // Get the channel mode
  const std::string& getMode() const;

//     // Get a list of usernames in the channel
//   std::vector<std::string> getUsernames() const;
    ~Channel();
};
