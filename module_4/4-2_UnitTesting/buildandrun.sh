#!/bin/bash

# ----- Color Definitions -----
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color (reset)

# ----- Build Steps -----
echo -e "${BLUE}Deleting old build directory if it exists...${NC}"
if [ -d "build" ]; then
	echo -e "\t${YELLOW}Old build directory found. Deleting...${NC}"
	rm -rf build/
	echo -e "\t${GREEN}Old build directory deleted.${NC}"
else
	echo -e "\t${GREEN}No old build directory found.${NC}"
fi

echo -e "${BLUE}Configuring the project with CMake...${NC}"
if ! cmake -S . -B build; then
	echo -e "\t${RED}CMake configuration failed.${NC}"
	exit 1
fi

echo -e "${BLUE}Building the project...${NC}"
if ! cmake --build build; then
	echo -e "\t${RED}Build failed.${NC}"
	exit 1
fi

echo -e "${BLUE}Build successful. Running tests...${NC}"
test_status=0
(
	cd build || exit 1
	ctest --output-on-failure || test_status=$?
)
if [ $test_status -ne 0 ]; then
	echo -e "\t${RED}Some tests failed.${NC}"
	exit $test_status
else
	echo -e "\t${GREEN}All tests passed successfully.${NC}"
fi
