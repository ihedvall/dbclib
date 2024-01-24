import pydbc
import logging


def test_envvar():
    logging.info("TESTING pydbc.EnvVar")

    env = pydbc.EnvVar()
    assert env is not None

    orig_name = "Obi-Wan"
    env.name = orig_name
    assert env.name == orig_name
    logging.debug("Name: " + env.name)

    orig_comment = "Canobi"
    env.comment = orig_comment
    assert env.comment == orig_comment
    logging.debug("Comment: " + env.comment)

    orig_type = pydbc.EnvType.FloatType
    env.type = orig_type
    assert env.type == orig_type

    orig_min = 11.0
    env.min = orig_min
    assert env.min == orig_min

    orig_max = 22.0
    env.max = orig_max
    assert env.max == orig_max

    orig_unit = "mph"
    env.unit = orig_unit
    assert env.unit == orig_unit
    logging.debug("Unit: " + env.unit)

    orig_init = 33.0
    env.initial_value = orig_init
    assert env.initial_value == orig_init

    orig_ident = 1234
    env.ident = orig_ident
    assert env.ident == orig_ident

    orig_access = pydbc.AccessType.ReadOnly
    env.access = orig_access
    assert env.access == orig_access
    logging.debug("Access: " + str(env.access))

    orig_node = ["Node 1", "Node2", "Node3" ]
    env.nodes = orig_node
    assert env.nodes == orig_node
    logging.debug("Node List: " + str(env.nodes))

    orig_enum = {
        0: "Zero",
        1: "One",
        2: "Two"
    }
    env.enumerate = orig_enum
    assert env.enumerate == orig_enum
    logging.debug("Enumerate: " + str(env.enumerate))
