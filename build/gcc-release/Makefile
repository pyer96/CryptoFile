build/gcc-release/bin/calendar_test: build/obj/4dbdf2fd/Progs/calendar_test.o

build/gcc-release/bin/calendar_test:
	g++ -o $@ $^ -libgoogleapis_curl_http -libgoogleapis_oauth2 -libgoogleapis_http -L$(HOME)/google-api-client-cpp/lib -fuse-ld=gold -s

build/gcc-release/bin/join_sections: build/obj/4e10544e/Progs/join_sections.o

build/gcc-release/bin/join_sections:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/link_test: build/obj/4dbdf2fd/Progs/link_test.o

build/gcc-release/bin/link_test:
	g++ -o $@ $^ -libgoogleapis_http -libgoogleapis_oauth2 -libgoogleapis_curl_http -L$(HOME)/google-api-client-cpp/lib -fuse-ld=gold -s

build/gcc-release/bin/make_sections: build/obj/4e10544e/Progs/make_sections.o

build/gcc-release/bin/make_sections:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/storage_test: build/obj/4dbdf2fd/Progs/storage_test.o

build/gcc-release/bin/storage_test:
	g++ -o $@ $^ -libgoogleapis_oauth2 -libgoogleapis_curl_http -libgoogleapis_http -L$(HOME)/google-api-client-cpp/lib -fuse-ld=gold -s

gcc-release: build/gcc-release/bin/calendar_test build/gcc-release/bin/join_sections build/gcc-release/bin/link_test build/gcc-release/bin/make_sections build/gcc-release/bin/storage_test

gcc-release-clean:
	rm -f build/gcc-release/bin/calendar_test build/gcc-release/bin/join_sections build/gcc-release/bin/link_test build/gcc-release/bin/make_sections build/gcc-release/bin/storage_test
	rm -f build/obj/4dbdf2fd/Progs/calendar_test.o build/obj/4dbdf2fd/Progs/link_test.o build/obj/4dbdf2fd/Progs/storage_test.o build/obj/4e10544e/Progs/join_sections.o build/obj/4e10544e/Progs/make_sections.o

