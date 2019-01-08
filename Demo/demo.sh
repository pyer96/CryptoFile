#!/ usr / bin / bash

FILE_NAME=$1
OUTPUT_FILE_NAME=$(dirname $FILE_NAME)"/copy_"$(basename $FILE_NAME)
SECTION_NUMBER=$2

printf "====make_sections====\n" &&
make ../build/gcc-release/bin/make_sections && ../build/gcc-release/bin/make_sections $FILE_NAME $SECTION_NUMBER &&
printf "\n====join_sections====\n" &&
make ../build/gcc-release/bin/join_sections && ../build/gcc-release/bin/join_sections $OUTPUT_FILE_NAME "$FILE_NAME"_* &&
printf "\n" &&
cmp $FILE_NAME $OUTPUT_FILE_NAME && printf "Success! $FILE_NAME and $OUTPUT_FILE_NAME are identical!\n"
