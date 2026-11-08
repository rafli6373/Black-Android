#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

// The renderer's HLSL (the SDK's translated shaders and the full screen passes) to SPIR-V with glslang, and a cache
// of the results on disk: compiling is slow on a phone and the same shaders come back every run.
// Bindings, one descriptor set: b0 and b1 at 0 and 1, t0 to t4 at 2 to 6, s0 to s4 at 7 to 11.
namespace vkshader {

constexpr uint32_t kBindingConstants = 0;  // b0..b1
constexpr uint32_t kBindingTextures = 2;   // t0..t4 (t4 = mythic weapon skin atlas)
constexpr uint32_t kBindingSamplers = 7;   // s0..s4 (s4 = mythic weapon skin sampler)
constexpr uint32_t kBindings = 12;

enum class Stage { Vertex, Pixel };

void Init(const std::filesystem::path& cache_dir);
// the SPIR-V of hlsl's entry point, named "main" in the module; false after logging why
bool Compile(const std::string& hlsl, const char* entry, Stage stage, uint64_t hash, std::vector<uint32_t>& spirv);

}  // namespace vkshader
