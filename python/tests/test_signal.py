import pydbc
import logging


def test_signal_value():
    logging.info("TESTING pydbc.SignalValue")

    value = pydbc.SignalValue()
    assert value is not None

    assert not value.valid
    value.valid = True
    assert value.valid

    assert value.signed_value == 0
    value.signed_value = -123
    assert value.signed_value == -123

    assert value.unsigned_value == 0
    value.unsigned_value = 123
    assert value.unsigned_value == 123

    assert value.float_value == 0.0
    value.float_value = 1.23
    assert value.float_value == 1.23

    assert value.array_value == []
    orig_array = [1, 2, 3]
    value.array_value = orig_array
    assert value.array_value == orig_array

    value.clear()
    assert not value.valid
    assert value.signed_value == 0
    assert value.unsigned_value == 0
    assert value.float_value == 0.0
    assert value.array_value == []


def test_extended_mux():
    logging.info("TESTING pydbc.ExtendedMux")

    mux = pydbc.ExtendedMux()
    assert mux is not None

    orig_multiplexor = "Yoda"
    mux.multiplexor = orig_multiplexor
    assert mux.multiplexor == orig_multiplexor

    orig_range_list = [(0, 10), (100, 110)]
    mux.range_list = orig_range_list
    logging.debug("Range List:" + str(mux.range_list))
    assert mux.range_list == orig_range_list
    assert mux.in_range(0)
    assert not mux.in_range(11)
    assert mux.in_range(110)


def test_signal():
    logging.info("TESTING pydbc.Signal")

    signal = pydbc.Signal()
    assert signal is not None

    orig_name = "Luke"
    signal.name = orig_name
    assert signal.name == orig_name

    orig_unit = "km/h"
    signal.unit = orig_unit
    assert signal.unit == orig_unit

    orig_comment = "km/h"
    signal.comment = orig_comment
    assert signal.comment == orig_comment

    orig_type = pydbc.SignalDataType.UnsignedData
    signal.data_type = orig_type
    assert signal.data_type == orig_type

    assert signal.mux == pydbc.MuxType.NotMultiplexed
    orig_mux = pydbc.MuxType.Multiplexor
    signal.mux = orig_mux
    assert signal.mux == orig_mux

    signal.mux_value = 1
    assert signal.mux_value == 1

    signal.bit_start = 4
    assert signal.bit_start == 4

    signal.bit_length = 24
    assert signal.bit_length == 24

    signal.little_endian = False
    assert not signal.little_endian

    signal.little_endian = True
    assert signal.little_endian

    assert signal.scale == 1
    assert signal.offset == 0

    signal.scale = 22
    signal.offset = 5
    assert signal.scale == 22
    assert signal.offset == 5

    signal.min = 4
    assert signal.min == 4
    signal.max = 20
    assert signal.max == 20

    orig_enum = {0: "Zero", 1: "One", 2: "Two"}
    signal.enumerate = orig_enum
    assert signal.enumerate == orig_enum

    orig_receivers = ["EMS", "EDU"]
    signal.receivers = orig_receivers
    assert signal.receivers == orig_receivers

    orig_attr = [pydbc.Attribute(pydbc.AttributeType.DbcSignal, "Trouble")]
    signal.attributes = orig_attr
    assert signal.attributes[0].name == orig_attr[0].name

    signal.message_id = 234
    assert signal.message_id == 234

    assert not signal.multiplexed
    assert not signal.array_value

    attr = signal.create_attribute(orig_attr[0])
    assert len(signal.attributes) == 2

    ext_mux = signal.extended_mux
    ext_mux.multiplexor = "Olle"
    logging.debug("Multiplexor: " + str(signal.extended_mux.multiplexor))
    assert signal.extended_mux.multiplexor == "Olle"

    assert signal.get_enum_string(1) == "One"

    assert signal.sample_counter == 0
    signal.step_sample_counter()
    assert signal.sample_counter == 1
    signal.reset_sample_counter()
    assert signal.sample_counter == 0

    assert signal.sample_time == 0

    signal_value = signal.signal_value
    signal_value.unsigned_value = 15
    logging.debug("Signal Value: " + str(signal.signal_value.unsigned_value))
    assert signal.signal_value.unsigned_value == 15

    signal.data_type = pydbc.SignalDataType.UnsignedData
    signal.valid = True
    signal.scale = 2.0
    signal.offset = 10.0
    signal.signal_value.valid = True
    signal.signal_value.unsigned_value = 333
    signal.enumerate = {}

    lrv = signal.channel_value
    assert lrv[0]
    assert lrv[1] == 333
    assert signal.channel_text_value[0]
    assert signal.channel_text_value[1] == "333"

    assert signal.eng_value[0]
    assert signal.eng_value[1] == 676
    assert signal.eng_text[0]
    assert signal.eng_text[1] == "676"
