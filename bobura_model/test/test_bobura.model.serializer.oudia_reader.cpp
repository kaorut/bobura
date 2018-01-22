/*! \file
    \brief Test of class bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/preprocessor.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/oudia_reader.h>
#include <bobura/model/serializer/select_oudia_diagram.h> // IWYU pragma: keep
#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_kind.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using station_location_type = timetable_type::station_location_type;

    using train_kind_type = timetable_type::train_kind_type;

    using color_type = ui_type_list_type::color_type;

    using train_type = timetable_type::train_type;

    using stop_type = train_type::stop_type;

    using time_type = stop_type::time_type;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using select_oudia_diagram_type = bobura::model::serializer::select_oudia_diagram_for_test<string_type>;

    using reader_type =
        bobura::model::serializer::oudia_reader<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            select_oudia_diagram_type,
            font_type,
            locale_type_list_type::windia_file_encoder_type
        >;

    using error_type = reader_type::error_type;


    // variables

    const std::string data_empty{};

    const std::string data_no_train{
        "FileType=OuDia.1.02\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=futsuu\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n"
    };

    const std::string data_full{
        "FileType=OuDia.1.02\n"
        "Rosen.\n"
        "Rosenmei=abc\n"
        "Eki.\n"
        "Ekimei=hoge\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsu\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=fuga\n"
        "Ekijikokukeisiki=Jikokukeisiki_NoboriChaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=piyo\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsuchaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=mnu\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsuchaku\n"
        "Ekikibo=Ekikibo_Syuyou\n"
        ".\n"
        "Eki.\n"
        "Ekimei=iroha\n"
        "Ekijikokukeisiki=Jikokukeisiki_NoboriChaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=nihohe\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsu\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=futsuu\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=Super Kaisoku\n"
        "Ryakusyou=SKai\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00ABCDEF\n"
        "DiagramSenStyle=SenStyle_Hasen\n"
        "DiagramSenIsBold=1\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "Dia.\n"
        "DiaName=Dia1\n"
        "Kudari.\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=0\n"
        "Ressyabangou=121D\n"
        "EkiJikoku=1;1000,1;1010,1;1020/1030,1;1040/1050,1;1100,1;1100\n"
        "Bikou=xyz\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=1\n"
        "Ressyabangou=101D\n"
        "Ressyamei=foo\n"
        "Gousuu=1\n"
        "EkiJikoku=1;1100,2,2,2;1130/1140,2,1;1150\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=0\n"
        "Ressyabangou=123D\n"
        "EkiJikoku=1;1200,1;1210,1;1220/1230,1;1240/,,\n"
        ".\n"
        ".\n"
        "Nobori.\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=0\n"
        "Ressyabangou=122D\n"
        "EkiJikoku=,,1;1000,1;1010/1020,1;1030/,1;1040\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=0\n"
        "Ressyabangou=124D\n"
        "EkiJikoku=1;1100,1;1110/,1;1120/1130,2;1140/1150,1;1200/,1;1210\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=1\n"
        "Ressyabangou=102D\n"
        "Ressyamei=bar\n"
        "Gousuu=2\n"
        "EkiJikoku=1;1200,2,2,2,2,1;1230\n"
        ".\n"
        "Dia.\n"
        "DiaName=Dia2\n"
        "Kudari.\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=0\n"
        "Ressyabangou=121D\n"
        "EkiJikoku=1;1000,1;1010,1;1020/1030,1;1040/1050,1;1100,1;1100\n"
        ".\n"
        ".\n"
        "Nobori.\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=0\n"
        "Ressyabangou=122D\n"
        "EkiJikoku=,,1;1000,1;1010/1020,1;1030/,1;1040\n"
        ".\n"
        ".\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=def\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n"
    };

    const std::string data_too_old_version{
        "FileType=OuDia.1.00\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=futsuu\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n"
    };

    const std::string data_too_new_version{
        "FileType=OuDia.1.03\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=futsuu\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n"
    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(oudia_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            const reader_type reader(std::move(p_select_diagram));
        }
        {
            std::unique_ptr<select_oudia_diagram_type> p_select_diagram{};
            BOOST_CHECK_THROW(reader_type(std::move(p_select_diagram)), std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_empty) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!reader.selects(first, last));
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_no_train) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(reader.selects(first, last));
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_too_old_version) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!reader.selects(first, last));
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_too_new_version) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!reader.selects(first, last));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_empty) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_no_train) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_TEST(p_timetable->line_name().empty());
            BOOST_TEST(p_timetable->note().empty());
            BOOST_TEST(p_timetable->station_locations().empty());

            BOOST_TEST_REQUIRE(p_timetable->train_kinds().size() == 1U);
            {
                const auto& train_kind = p_timetable->train_kinds()[0];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("futsuu") });
                BOOST_CHECK((train_kind.diagram_color() == color_type{ 0, 0, 0 }));
                BOOST_CHECK(train_kind.diagram_line_weight() == train_kind_type::weight_type::normal);
            }

            BOOST_TEST(p_timetable->down_trains().empty());
            BOOST_TEST(p_timetable->up_trains().empty());
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_full) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("abc") });
            BOOST_CHECK(p_timetable->note() == string_type{ TETENGO2_TEXT("def") });

            BOOST_TEST_REQUIRE(p_timetable->station_locations().size() == 6U);
            {
                const auto& station_location = p_timetable->station_locations()[0];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("hoge") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_TEST(station_location.operating_distance() == 0U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[2];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("piyo") });
                BOOST_CHECK(
                    station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local terminal") }
                );
                BOOST_TEST(station_location.operating_distance() == 2U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[4];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("iroha") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_TEST(station_location.get_station().shows_up_arrival_times());
                BOOST_TEST(station_location.operating_distance() == 4U);
            }

            BOOST_TEST_REQUIRE(p_timetable->train_kinds().size() == 2U);
            {
                const auto& train_kind = p_timetable->train_kinds()[0];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("futsuu") });
                BOOST_CHECK((train_kind.diagram_color() == color_type{ 0, 0, 0 }));
                BOOST_CHECK(train_kind.diagram_line_weight() == train_kind_type::weight_type::normal);
            }
            {
                const auto& train_kind = p_timetable->train_kinds()[1];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("Super Kaisoku") });
                BOOST_CHECK((train_kind.diagram_color() == color_type{ 0xAB, 0xCD, 0xEF }));
                BOOST_CHECK(train_kind.diagram_line_weight() == train_kind_type::weight_type::bold);
            }

            BOOST_TEST_REQUIRE(p_timetable->down_trains().size() == 3U);
            {
                const auto& train = p_timetable->down_trains()[0];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("121D") });
                BOOST_TEST(train.name().empty());
                BOOST_TEST(train.kind_index() == 0U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 10, 0, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 10, 20, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 10, 30, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                BOOST_CHECK(train.note() == string_type{ TETENGO2_TEXT("xyz") });
            }
            {
                const auto& train = p_timetable->down_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("101D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("foo") });
                BOOST_TEST(train.kind_index() == 1U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 11, 0, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[3];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 30, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 40, 0 }));
                    BOOST_TEST(stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }

            BOOST_TEST_REQUIRE(p_timetable->up_trains().size() == 3U);
            {
                const auto& train = p_timetable->up_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("124D") });
                BOOST_TEST(train.name().empty());
                BOOST_TEST(train.kind_index() == 0U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 40, 00 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 50, 00 }));
                    BOOST_TEST(stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[4];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 10, 0 }));
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->up_trains()[2];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("102D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("bar") });
                BOOST_TEST(train.kind_index() == 1U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[4];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia2") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_full) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_TEST(p_timetable->down_trains().size() == 1U);
            BOOST_TEST(p_timetable->up_trains().size() == 1U);
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia3") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_full) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::canceled);
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_too_old_version) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            auto p_select_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(string_type{ TETENGO2_TEXT("Dia1") });
            reader_type reader(std::move(p_select_diagram));

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data_too_new_version) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
