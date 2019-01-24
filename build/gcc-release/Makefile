build/gcc-release/bin/bing_search: build/obj/19999c00/Progs/bing_search.o

build/gcc-release/bin/bing_search:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/calendar_test: build/obj/19999c00/Progs/calendar_test.o

build/gcc-release/bin/calendar_test:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/cpprest_hello_world: build/obj/19999c00/Progs/cpprest_hello_world.o

build/gcc-release/bin/cpprest_hello_world:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/crypto_file: build/obj/19999c00/CryptoFile/Auth/AuthListener.o
build/gcc-release/bin/crypto_file: build/obj/19999c00/CryptoFile/Auth/ServiceAuth.o
build/gcc-release/bin/crypto_file: build/obj/19999c00/CryptoFile/CryptoFile.o
build/gcc-release/bin/crypto_file: build/obj/19999c00/Progs/crypto_file.o

build/gcc-release/bin/crypto_file:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/crypto_test: build/obj/19999c00/Progs/crypto_test.o

build/gcc-release/bin/crypto_test:
	g++ -o $@ $^ -lcryptopp -lpthread -fuse-ld=gold -s

build/gcc-release/bin/dropbox: build/obj/19999c00/Progs/dropbox.o

build/gcc-release/bin/dropbox:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/http_get: build/obj/19999c00/Progs/http_get.o

build/gcc-release/bin/http_get:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/http_request: build/obj/19999c00/Progs/http_request.o

build/gcc-release/bin/http_request:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/http_request2: build/obj/19999c00/Progs/http_request2.o

build/gcc-release/bin/http_request2:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/join_sections: build/obj/19999c00/Progs/join_sections.o

build/gcc-release/bin/join_sections:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/link_status: build/obj/19999c00/Progs/link_status.o

build/gcc-release/bin/link_status:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/link_test: build/obj/19999c00/Progs/link_test.o

build/gcc-release/bin/link_test:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/make_sections: build/obj/19999c00/Progs/make_sections.o

build/gcc-release/bin/make_sections:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/regex_test: build/obj/19999c00/Progs/regex_test.o

build/gcc-release/bin/regex_test:
	g++ -o $@ $^ -fuse-ld=gold -s

build/gcc-release/bin/rest_api_test: build/obj/19999c00/Progs/rest_api_test.o

build/gcc-release/bin/rest_api_test:
	g++ -o $@ $^ -lboost_system -lcrypto -lssl -lcpprest -lpthread -fuse-ld=gold -s

build/gcc-release/bin/storage_test: build/obj/19999c00/Progs/storage_test.o

build/gcc-release/bin/storage_test:
	g++ -o $@ $^ -fuse-ld=gold -s

gcc-release: build/gcc-release/bin/bing_search build/gcc-release/bin/calendar_test build/gcc-release/bin/cpprest_hello_world build/gcc-release/bin/crypto_file build/gcc-release/bin/crypto_test build/gcc-release/bin/dropbox build/gcc-release/bin/http_get build/gcc-release/bin/http_request build/gcc-release/bin/http_request2 build/gcc-release/bin/join_sections build/gcc-release/bin/link_status build/gcc-release/bin/link_test build/gcc-release/bin/make_sections build/gcc-release/bin/regex_test build/gcc-release/bin/rest_api_test build/gcc-release/bin/storage_test

gcc-release-clean:
	rm -f build/gcc-release/bin/bing_search build/gcc-release/bin/calendar_test build/gcc-release/bin/cpprest_hello_world build/gcc-release/bin/crypto_file build/gcc-release/bin/crypto_test build/gcc-release/bin/dropbox build/gcc-release/bin/http_get build/gcc-release/bin/http_request build/gcc-release/bin/http_request2 build/gcc-release/bin/join_sections build/gcc-release/bin/link_status build/gcc-release/bin/link_test build/gcc-release/bin/make_sections build/gcc-release/bin/regex_test build/gcc-release/bin/rest_api_test build/gcc-release/bin/storage_test
	rm -f build/obj/19999c00/CryptoFile/Auth/AuthListener.o build/obj/19999c00/CryptoFile/Auth/ServiceAuth.o build/obj/19999c00/CryptoFile/CryptoFile.o build/obj/19999c00/Progs/bing_search.o build/obj/19999c00/Progs/calendar_test.o build/obj/19999c00/Progs/cpprest_hello_world.o build/obj/19999c00/Progs/crypto_file.o build/obj/19999c00/Progs/crypto_test.o build/obj/19999c00/Progs/dropbox.o build/obj/19999c00/Progs/http_get.o build/obj/19999c00/Progs/http_request.o build/obj/19999c00/Progs/http_request2.o build/obj/19999c00/Progs/join_sections.o build/obj/19999c00/Progs/link_status.o build/obj/19999c00/Progs/link_test.o build/obj/19999c00/Progs/make_sections.o build/obj/19999c00/Progs/regex_test.o build/obj/19999c00/Progs/rest_api_test.o build/obj/19999c00/Progs/storage_test.o

