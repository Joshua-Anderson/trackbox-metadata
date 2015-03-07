#include <iostream>
#include <vector>
#include <sstream>


#include <fileref.h>
#include <tag.h>
#include <tstring.h>
#include <tpropertymap.h>

#include "version.h"

struct output {
  TagLib::String key;
  TagLib::String value;
};

typedef std::vector<output> JSON;

void printJSON(output o) {
  std::cout << '{' << std::endl;
  std::cout << "\t\"" << o.key << "\" : \"" << o.value << "\"\n";
  std::cout << '}' << std::endl;
}

void printJSON(JSON vo) {
  std::cout << '{' << std::endl;

  for(unsigned int i=0; i < vo.size(); i++) {
    output o = vo[i];
    std::cout << "\t\"" << o.key << "\" : \"" << o.value << "\"";

    if(i < vo.size()-1) {
      std::cout << ",";
    }

    std::cout << std::endl;
  }

  std::cout << '}' << std::endl;
}

int main(int argc, char *argv[])
{
   int filepath_arg = -1;

  for(int i=1; argc > 1 && i < argc; i++) {
    TagLib::String arg = argv[i];

    if(arg == "--version" || arg == "--help"|| arg == "-v" || arg == "-h") {
      JSON message;

      output name = {"name", "trackbox-metadata"};
      output about = {"about", "reads and modifies music metadata"};
      output version = {"version", VERSION};
      output authors = {"authors", "Joshua Anderson and Keavon ChambersS"};
      output homepage = {"homepage", "https://github.com/Trackbox/trackbox-metadata"};

      message.push_back(name);
      message.push_back(about);
      message.push_back(version);
      message.push_back(authors);
      message.push_back(homepage);

      printJSON(message);
      return 0;
    }

    if(arg.substr(0,2) != "--") {
      filepath_arg = i;
    }
  }

  if(filepath_arg > 0) {
    TagLib::FileRef file(argv[filepath_arg]);

    if(!file.isNull() && file.tag()) {
      TagLib::Tag *tag = file.tag();
      TagLib::String songTitle = tag->title();
      TagLib::String songArtist = tag->artist();
      TagLib::String songAlbum = tag->album();
      TagLib::String songComment = tag->comment();
      TagLib::String songGenre = tag->genre();
      unsigned int songTrack = tag->track();
      unsigned int songYear = tag->year();


      JSON metadata;

      output path = {"path", argv[filepath_arg]};
      metadata.push_back(path);

      if(songTitle != TagLib::String::null) {
        output title = {"title", songTitle};
        metadata.push_back(title);
      }

      if(songArtist != TagLib::String::null) {
        output artist = {"artist", songArtist};
        metadata.push_back(artist);
      }

      if(songAlbum != TagLib::String::null) {
        output album = {"album", songAlbum};
        metadata.push_back(album);
      }

      if(songComment != TagLib::String::null) {
        output comment = {"comment", songComment};
        metadata.push_back(comment);
      }

      if(songGenre != TagLib::String::null) {
        output genre = {"genre", songGenre};
        metadata.push_back(genre);
      }

      if(songTrack > 0) {
        std::stringstream stream;
        stream << songTrack;
        TagLib::String songTrackString = stream.str();
        output track = {"track", songTrackString};
        metadata.push_back(track);
      }

      if(songYear > 0) {
        std::stringstream stream;
        stream << songYear;
        TagLib::String songYearString = stream.str();
        output year = {"year", songYearString};
        metadata.push_back(year);
      }

      printJSON(metadata);
    }
  } else {
    output warning = {"warning", "no song passed, exiting"};
    printJSON(warning);
  }

  if(argc == 1) {
    output warning = {"warning", "no arguments passed, exiting"};
    printJSON(warning);
  }



  return 0;
}
