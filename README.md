Trackbox Metadata
-----------------

A command line program that reads and writes metadata for music files. Currently in development.

### Usage

``` console
$ trackbox-metadata /path/to/song.mp3

{
  "path" : "path to song",
  "song" : "song name",
  "artist" : "artist",
  "album" : "album",
  "comment" : "comment",
  "genre" : "genre",
  "track": "track number",
  "year" : "year"
}
```

If a piece of metadata is not available it will not be printed.

### Building

##### Linux

You need to have `cmake`, `gcc`, and `make` installed.

```
$ mkdir build & cd build
$ cmake -DCMAKE_BUILD_TYPE=Release
$ make -j5 # Or number of cores + 1
```
