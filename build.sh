rm -rf build/
rm -rf distr/
mkdir build
mkdir distr
cd build
emcmake cmake ../
make
cd ..
find distr/ -type f -name "*.wasm.*" -exec cp {} public/ \;