import pydbc
import logging
import time


def test_dbc_message():
    logging.info("TESTING pydbc::DbcMessage")

    msg = pydbc.DbcMessage()
    assert msg is not None

    orig_time = time.time_ns()
    msg.time = orig_time
    assert msg.time == orig_time

    orig_can_id = 12345
    msg.can_id = orig_can_id
    assert msg.can_id == orig_can_id

    orig_list = [1, 2, 3, 255]
    msg.data = orig_list
    assert msg.data == orig_list

    msg1 = pydbc.DbcMessage(orig_time, orig_can_id, orig_list)
    assert msg1 is not None
    assert msg1.time == orig_time
    assert msg1.can_id == orig_can_id
    assert msg1.data == orig_list
    logging.debug("Message 1: " + str(msg1.data))