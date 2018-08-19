#include <Rcpp.h>
using namespace Rcpp;
#include "geolocChina.h"
#include "na_list.h"


// Exported function. Takes as input a char vector of Chinese strings, sends 
// each one through get_locations() in a loop (along with the geolocChina 
// package data). Returns a data frame of geolocation data related to each 
// input string.
// [[Rcpp::export]]
DataFrame cpp_geo_locate(const CharacterVector &cn_strings) {
  
  int cn_strings_len = cn_strings.size();
  std::unordered_map<std::string, int> substr_map;
  std::string matches;
  
  // If input cn_strings is all NA values, then return a data frame full of NA
  // values.
  if(is_true(all(is_na(cn_strings)))) {
    return(get_na_dataframe(cn_strings_len));
  }
  
  List res(cn_strings_len);
  List out;
  
  // Loop over cn_strings, get geolocations and geocodes for each string.
  for(int i = 0; i < cn_strings_len; ++i) {
    if(CharacterVector::is_na(cn_strings[i])) {
      res[i] = na_list;
    } else {
      const std::string &curr_cn_str = as<std::string>(cn_strings[i]);
      get_locations(curr_cn_str, substr_map, matches, out);
      res[i] = out;
    }
  }
  
  DataFrame out_df = DataFrame::create(
    Named("location") = cn_strings,
    Named("province") = extract_char_vector(res, 0),
    Named("city") = extract_char_vector(res, 1),
    Named("county") = extract_char_vector(res, 2),
    Named("province_code") = extract_int_vector(res, 3),
    Named("city_code") = extract_int_vector(res, 4),
    Named("county_code") = extract_int_vector(res, 5), 
    Named("stringsAsFactors") = false
  );
  
  return(out_df);
}
