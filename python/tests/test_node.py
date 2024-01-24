import pydbc
import logging


def test_node():
    logging.info("TESTING pydbc.Node")

    node = pydbc.Node()
    assert node is not None

    orig_name = "Michael"
    node.name = orig_name
    assert node.name == orig_name
    logging.debug("Name: " + str(node.name))

    orig_comment = "Burnham"
    node.comment = orig_comment
    assert node.comment == orig_comment
    logging.debug("Comment: " + str(node.comment))

    node.source = 11
    assert node.source == 11

    assert len(node.attributes) == 0
    templ = pydbc.Attribute()
    attr_name = "Tilly"
    attr = node.create_attribute(templ)
    attr.name = attr_name
    assert len(node.attributes) == 1
    assert node.attributes[0].name == attr_name
    attr1 = node.get_attribute(attr_name)
    assert attr1.name == attr_name
