#include <iostream>
#include <dbc/dbcfile.h>


int main() {
    dbc::DbcFile file;

    file.Filename(DBC_FILE_PATH);
    const auto success = file.ParseFile();

    auto* network = file.GetNetwork();
    const auto& message_list = network->Messages();
    for (const auto& itr : message_list) {
      const auto& message = itr.second;
      std::cout << "ID: " << message.CanId()
                << (message.IsExtended() ? "E" : "S")
                << ", Name: " << message.Name()
                << ", Bytes: " << message.NofBytes()
                << ", Node: " << message.Node()
                << ". Comment: " << message.Comment()
                << std::endl;
    }
}
