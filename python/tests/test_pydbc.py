
import pydbc
import pytest
import logging
import time


def test_dbc_file():
    dbc = pydbc.DbcFile()
    assert dbc is not None

    file_path = "c:/xxx/yyy/olle.dbc"
    dbc.filename = file_path
    assert dbc.filename == file_path
    logging.debug(dbc.filename)

    assert dbc.name == "olle"
    logging.debug(dbc.name)

    base_time = time.time_ns()
    dbc.base_time = base_time
    assert dbc.base_time == base_time
    logging.debug(dbc.base_time)
