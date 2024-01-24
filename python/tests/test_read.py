import unittest
import os
import logging
import pydbc

DBC_SOURCE_DIR = "k:/test/dbc"


class TestDbcRead(unittest.TestCase):
    dbc_list = []

    def setUp(self) -> None:

        self.dbc_list.clear()
        if not os.path.exists(DBC_SOURCE_DIR):
            return
        for (dir_path, dirs, files) in os.walk(DBC_SOURCE_DIR):
            for filename in files:
                stem, ext = os.path.splitext(filename)
                if ext == ".dbc":
                    full_name = os.path.join(dir_path, filename)
                    self.dbc_list.append(full_name)

    def test_check_parser(self):
        logging.info("TESTING pydbc::TestDbcRead::test_check_parser")
        if len(self.dbc_list) == 0:
            self.skipTest("No DBC files to test")
        for file in self.dbc_list:
            dbc_file = pydbc.DbcFile()
            dbc_file.filename = file
            parse = dbc_file.parse_file()
            self.assertTrue(parse,"File: " + dbc_file.filename + ", Error: " + dbc_file.last_error )
            logging.debug("File: " + dbc_file.filename )

    def test_check_message(self):
        logging.info("TESTING pydbc::TestDbcRead::test_check_message")
        if len(self.dbc_list) == 0:
            self.skipTest("No DBC files to test")
        dbc_file = pydbc.DbcFile()
        dbc_file.filename = self.dbc_list[0]
        parse = dbc_file.parse_file()
        self.assertTrue(parse, "File: " + dbc_file.filename + ", Error: " + dbc_file.last_error)

        network = dbc_file.get_network()
        self.assertIsNotNone(network,  dbc_file.name)

        messages = network.messages
        for msg_id in network.messages:
            msg = messages[msg_id]
            logging.debug("CAN ID:" + str(msg.can_id) + ", Name: " + msg.name)
            self.assertGreater(msg.nof_bytes, 0, msg.name)
            for signal_name in msg.signals:
                signal = msg.signals[signal_name]
                signal1 = msg.get_signal(signal.name)
                self.assertEqual(signal.name, signal1.name)
                logging.debug("Signal Name: " + signal.name)


if __name__ == '__main__':
    unittest.main()
