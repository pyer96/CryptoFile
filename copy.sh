#!/usr/bin/bash



printf "====make_sections====\n" &&
rm elefant_* &&
g++ make_sections.cpp -o make_sections && ./make_sections &&
printf "\n====join_sections====\n" &&
g++ join_sections.cpp -o join_sections && ./join_sections elefant_? &&
printf "\n" &&
for name in *; do
  echo "$name `wc -c <$name`" |grep "elefant"
done
