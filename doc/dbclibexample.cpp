#include <iostream>
#include <dbc/dbcfile.h>


int main() {
    dbc::DbcFile file;

    file.Filename(DBC_FILE_PATH); // File path to the dbc file
    bool success = file.ParseFile();

    auto* network = file.GetNetwork();
    const auto& message_list = network->Messages();
    for (const auto& itr : message_list) {
      // Message properties
      const dbc::Message& message = itr.second;
      std::cout << "ID: " << message.CanId()
                << (message.IsExtended() ? "E" : "S")
                << ", Name: " << message.Name()
                << ", Bytes: " << message.NofBytes()
                << ", Node: " << message.NodeName()
                << ". Comment: " << message.Comment()
                << std::endl;

      // Signals and properties
      const auto& signal_list = message.Signals();
      for (const auto& itr: signal_list) {
          const dbc::Signal& signal = itr.second;
          std::string datatype = "Uknown";
          switch (signal.DataType()) {
              case dbc::SignalDataType::SignedData: datatype = "SignedData"; break;
              case dbc::SignalDataType::UnsignedData: datatype = "UnsignedData"; break;
              case dbc::SignalDataType::FloatData: datatype = "FloatData"; break;
              case dbc::SignalDataType::DoubleData: datatype = "DoubleData"; break;
          }


          std::cout << "Name: " << signal.Name()
                    << ", Bit Start: " << signal.BitStart()
                    << ", Length: " << signal.BitLength()
                    << ", Endian: " << (signal.LittleEndian() ? "Little" : "Big")
                    << ", Datatype: " << datatype
                    << ", Scale: " << signal.Scale()
                    << ", Offset: " << signal.Offset()
                    << ", Min: " << signal.Min()
                    << ", Max: " << signal.Max()
                    << ", Unit: " << signal.Unit()
                    << ", Receiver: ";
          for (int i=0; i < signal.Receivers().size() - 1; i++) {
              std::cout << signal.Receivers().at(i) << ",";
          }
          if (!signal.Receivers().empty())
            std::cout << signal.Receivers().at(signal.Receivers().size() - 1) << std::endl;
      }
    }

    // ##################################################################################
    // Parsing a message
    // ##################################################################################

    dbc::DbcMessage msg(0, 234, {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8});
    success = file.ParseMessage(msg);
    dbc::Message* message = network->GetMessage(234);
    if (message) {
        for (const auto& signalPair: message->Signals()) {
            double value;
            const dbc::Signal& signal = signalPair.second;
            signalPair.second.EngValue(value);

            std::cout << "Signal: " << signal.Name()
                      << ", Value: " << value << " " << signal.Unit()
                      << std::endl;
        }
    }

}
