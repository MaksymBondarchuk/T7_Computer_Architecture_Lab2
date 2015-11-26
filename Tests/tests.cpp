//
// Created by max on 20.09.15.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Decoder_tests

#include <boost/test/unit_test.hpp>
#include "../Decoder/Decoder.h"


BOOST_AUTO_TEST_CASE(testing_Decoder_class) {
    Decoder d = Decoder();
    BOOST_CHECK_EQUAL(d.encode_one_symbol("A"), "-.---");
    BOOST_CHECK_EQUAL(d.encode_one_symbol(""), "");
    BOOST_CHECK_EQUAL(d.encode_one_symbol("abc"), "");

    BOOST_CHECK_EQUAL(d.decode_one_symbol("-.---"), "A");
    BOOST_CHECK_EQUAL(d.decode_one_symbol(""), "");
    BOOST_CHECK_EQUAL(d.decode_one_symbol("-.-----"), "");

    BOOST_CHECK_EQUAL(d.decode("-.-.-...---.---.---...---.---...-.......---...-...---.-.-.---...---"), "SOME TEXT");
    BOOST_CHECK_EQUAL(d.decode(
            "-.-.-...---.---.---...---.---...-.......---.---.---...---...-.-.-.-...-...-.---.-.......---...-...---.-.-.---...---"),
                      "SOME OTHER TEXT");
    BOOST_CHECK_EQUAL(d.decode("-.-----"), "");

    BOOST_CHECK_EQUAL(d.encode("SOME TEXT"), "-.-.-...---.---.---...---.---...-.......---...-...---.-.-.---...---");
    BOOST_CHECK_EQUAL(d.encode("SOME OTHER TEXT"),
                      "-.-.-...---.---.---...---.---...-.......---.---.---...---...-.-.-.-...-...-.---.-.......---...-...---.-.-.---...---");
    BOOST_CHECK_EQUAL(d.encode(""), "");

    vector<string> v = d.split("word0 word1 word2", " ");
    BOOST_CHECK_EQUAL("word0", v[0]);
    BOOST_CHECK_EQUAL("word1", v[1]);
    BOOST_CHECK_EQUAL("word2", v[2]);

    v = d.split("word0...word1...word2...", "...");
    BOOST_CHECK_EQUAL("word0", v[0]);
    BOOST_CHECK_EQUAL("word1", v[1]);
    BOOST_CHECK_EQUAL("word2", v[2]);
    BOOST_CHECK_EQUAL("", v[3]);

}
