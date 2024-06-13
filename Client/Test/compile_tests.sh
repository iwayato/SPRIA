mkdir -p "/build"

if [ -z "$1" ]; then
    echo "No source file provided"
    exit 1
fi

if [ -z "$2" ]; then
    echo "No name for bin file provided."
    exit 1
fi

g++ $1 -o $2 -I /usr/local/boost_1_82_0/