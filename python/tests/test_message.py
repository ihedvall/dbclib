import pydbc
import logging


def test_message():
    logging.info("TESTING pydbc.Message")

    msg = pydbc.Message()
    assert msg is not None

    assert msg.message_id == 0
    msg.message_id = 10123
    assert msg.message_id == 10123
    logging.debug("Message ID: " + str(msg.message_id))

    orig_name = "James"
    msg.name = orig_name
    assert msg.name == orig_name
    logging.debug("Name: " + str(msg.name))

    orig_comment = "Kirk"
    msg.comment = orig_comment
    assert msg.comment == orig_comment
    logging.debug("Comment: " + str(msg.comment))

    templ = pydbc.Attribute()
    assert templ is not None

    attr_name = "Spock"
    attr = msg.create_attribute(templ)
    assert attr is not None
    attr.name = attr_name
    assert attr.name == attr_name
    assert len(msg.attributes) == 1
    assert msg.attributes[0].name == attr_name

    attr1 = msg.get_attribute(attr_name)
    assert attr is not None
    assert attr1.name == attr_name

    msg.nof_bytes = 7
    assert msg.nof_bytes == 7

    node_name = "Enterprise"
    msg.add_node(node_name)
    assert msg.node_name == node_name

    invalid_signal = msg.get_signal("foo")
    assert invalid_signal is None

    signal_name = "Pike"
    signal = msg.create_signal(signal_name)
    assert signal is not None
    assert signal.name == signal_name

    signal1 = msg.get_signal(signal_name)
    assert signal1 is not None
    assert signal1.name == signal.name
    assert len(msg.signals) == 1
    assert msg.signals[signal_name].name == signal_name

    multiplexor = msg.get_multiplexor()
    assert multiplexor is None

    assert len(msg.senders) == 1
    assert msg.senders[0] == node_name
    assert msg.node_sender(node_name)
    assert not msg.node_sender("Chapel")

    # Note that nof_bytes == 7 is set earlier
    data_list_short = [0, 1]
    assert not msg.update_data(data_list_short)
    data_list = [0, 1, 2, 3, 4, 5, 6]
    assert msg.update_data(data_list, 0, 0)
    assert msg.data == data_list
    logging.debug("Data: " + str(msg.data))

    msg.parse_message(0, 10123)

    msg.reset_sequence_number()
    assert msg.sequence_number == 0

    msg.reset_sample_counter()
    assert msg.sample_counter == 0
    msg.step_sample_counter()
    assert msg.sample_counter == 1



