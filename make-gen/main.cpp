#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
  const auto outDir = "";
  const auto sndDir = "snd/";
  const auto spriteDir = "sprite/";
  std::vector<std::string> wavs;
  for (const auto &file : std::filesystem::directory_iterator(sndDir))
    if (file.path().extension() == ".wav")
      wavs.push_back(file.path().stem());
  std::vector<std::string> bmps;
  for (const auto &file : std::filesystem::directory_iterator(spriteDir))
    if (file.path().extension() == ".tif")
      bmps.push_back(file.path().stem());

  std::cout << "ALL:";

  for (auto p : wavs)
    std::cout << " " << outDir << p << ".wav.gen.hpp";
  for (auto p : bmps)
    std::cout << " " << outDir << p << ".bmp.gen.hpp";
  std::cout << "\n\techo done\n";
  for (auto p : wavs)
  {
    std::cout << outDir << p << ".wav.gen.hpp: " << sndDir << p << ".wav\n"
              << "\txxd -i " << sndDir << p << ".wav > " << outDir << p << ".wav.gen.hpp\n";
  }
  for (auto p : bmps)
  {
    std::cout << outDir << p << ".bmp.gen.hpp: " << spriteDir << p << ".bmp\n"
              << "\txxd -i " << spriteDir << p << ".bmp > " << outDir << p << ".bmp.gen.hpp\n";
    std::cout << spriteDir << p << ".bmp: " << spriteDir << p << ".tif\n"
              << "\tconvert " << spriteDir << p << ".tif " << spriteDir << p << ".bmp\n";
  }
}
