//
// Created by max on 20.09.15.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Decoder_tests

#include <boost/test/unit_test.hpp>
#include "../Decoder/Decoder.hpp"


BOOST_AUTO_TEST_CASE(testing_Decoder_class) {
    Decoder d = Decoder();
    BOOST_CHECK_EQUAL(d.EncodeOneSymbol("A"), "-.---");
    BOOST_CHECK_EQUAL(d.EncodeOneSymbol(""), "");
    BOOST_CHECK_EQUAL(d.EncodeOneSymbol("abc"), "");

    BOOST_CHECK_EQUAL(d.DecodeOneSymbol("-.---"), "A");
    BOOST_CHECK_EQUAL(d.DecodeOneSymbol(""), "");
    BOOST_CHECK_EQUAL(d.DecodeOneSymbol("-.-----"), "");

    BOOST_CHECK_EQUAL(d.Decode("-.-.-...---.---.---...---.---...-.......---...-...---.-.-.---...---"), "SOME TEXT");
    BOOST_CHECK_EQUAL(d.Decode(
            "-.-.-...---.---.---...---.---...-.......---.---.---...---...-.-.-.-...-...-.---.-.......---...-...---.-.-.---...---"),
                      "SOME OTHER TEXT");
    BOOST_CHECK_EQUAL(d.Decode("-.-----"), "");

    BOOST_CHECK_EQUAL(d.Encode("SOME TEXT"), "-.-.-...---.---.---...---.---...-.......---...-...---.-.-.---...---");
    BOOST_CHECK_EQUAL(d.Encode("SOME OTHER TEXT"),
                      "-.-.-...---.---.---...---.---...-.......---.---.---...---...-.-.-.-...-...-.---.-.......---...-...---.-.-.---...---");
    BOOST_CHECK_EQUAL(d.Encode(""), "");

    vector<string> v = d.Split("word0 word1 word2", " ");
    BOOST_CHECK_EQUAL("word0", v[0]);
    BOOST_CHECK_EQUAL("word1", v[1]);
    BOOST_CHECK_EQUAL("word2", v[2]);

    v = d.Split("word0...word1...word2...", "...");
    BOOST_CHECK_EQUAL("word0", v[0]);
    BOOST_CHECK_EQUAL("word1", v[1]);
    BOOST_CHECK_EQUAL("word2", v[2]);
    BOOST_CHECK_EQUAL("", v[3]);

}
