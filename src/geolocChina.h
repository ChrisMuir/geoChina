#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]


// Unpack values from pkg data list into vectors.
const Environment &geoloc_env = Environment::namespace_env("geolocChina");
const Environment &cn_env = geoloc_env["cn_env"];
const List &pkg_data = cn_env["geo_data"];

const std::vector<std::string> &prov_dd_strings = pkg_data[0];
const std::vector<int> prov_dd_codes = pkg_data[1];
const std::vector<std::string> &city_dd_strings = pkg_data[2];
const std::vector<int> city_dd_codes = pkg_data[3];
const std::vector<std::string> &cnty_dd_strings = pkg_data[4];
const std::vector<int> cnty_dd_codes = pkg_data[5];
const std::vector<std::string> &cnty_dd_strings_2015 = pkg_data[6];
const std::vector<int> cnty_dd_codes_2015 = pkg_data[7];

// Record lengths of some of the pkg data vectors.
const int &prov_dd_len = prov_dd_strings.size();
const int &city_dd_len = city_dd_strings.size();
const int &cnty_dd_len = cnty_dd_strings.size();
const int &cnty_dd_2015_len = cnty_dd_strings_2015.size();

// Create set of city codes, to use as a reference when attempting to assign 
// a city code from a matched county code.
const std::unordered_set<int> city_code_set(city_dd_codes.begin(), 
                                            city_dd_codes.end());

// Create list of NA values.
List na_res = List::create(NA_STRING, NA_STRING, NA_STRING, NA_INTEGER, 
                           NA_INTEGER, NA_INTEGER);