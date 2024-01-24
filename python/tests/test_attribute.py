import pydbc
import logging


def test_attribute():
    logging.info("TESTING pydbc.Attribute")

    attr = pydbc.Attribute()
    assert attr is not None

    orig_name = "Obi-Wan"
    attr.name = orig_name
    assert attr.name == orig_name
    logging.debug("Name: " + attr.name)

    orig_type = pydbc.AttributeType.DbcSignal
    attr.type = orig_type
    assert attr.type == orig_type

    orig_value_type = pydbc.AttributeValueType.HexValue
    attr.value_type = orig_value_type
    assert attr.value_type == orig_value_type

    orig_min = 11.0
    attr.min = orig_min
    assert attr.min == orig_min

    orig_max = 22.0
    attr.max = orig_max
    assert attr.max == orig_max

    orig_enum = ["Zero", "One", "Two"]
    attr.enumerate = orig_enum
    assert attr.enumerate == orig_enum

    orig_value = 11
    attr.value = 11
    assert attr.value == orig_value

    logging.info(help(pydbc.Signal))
