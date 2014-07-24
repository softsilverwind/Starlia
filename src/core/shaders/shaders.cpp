const char *shaders_basiccolor_f = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x33\x20\x66\x5f\x63\x6f\x6c\x6f\x72\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x20\x20\x20\x20\x67\x6c\x5f\x46\x72\x61\x67\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x76\x65\x63\x34\x28\x66\x5f\x63\x6f\x6c\x6f\x72\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x7d\x0a";
const char *shaders_basiccolor_v = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x33\x20\x70\x6f\x73\x3b\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x33\x20\x63\x6f\x6c\x6f\x72\x3b\x0a\x0a\x75\x6e\x69\x66\x6f\x72\x6d\x20\x6d\x61\x74\x34\x20\x77\x76\x70\x3b\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x33\x20\x66\x5f\x63\x6f\x6c\x6f\x72\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x09\x67\x6c\x5f\x50\x6f\x73\x69\x74\x69\x6f\x6e\x20\x3d\x20\x77\x76\x70\x20\x2a\x20\x76\x65\x63\x34\x28\x70\x6f\x73\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x09\x66\x5f\x63\x6f\x6c\x6f\x72\x20\x3d\x20\x63\x6f\x6c\x6f\x72\x3b\x0a\x7d\x0a";
const char *shaders_basicobject_f = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x32\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x75\x6e\x69\x66\x6f\x72\x6d\x20\x73\x61\x6d\x70\x6c\x65\x72\x32\x44\x20\x74\x65\x78\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x20\x20\x20\x20\x76\x65\x63\x32\x20\x66\x6c\x69\x70\x70\x65\x64\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x20\x3d\x20\x76\x65\x63\x32\x28\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x2e\x78\x2c\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x2e\x79\x29\x3b\x0a\x20\x20\x20\x20\x67\x6c\x5f\x46\x72\x61\x67\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x74\x65\x78\x74\x75\x72\x65\x32\x44\x28\x74\x65\x78\x2c\x20\x66\x6c\x69\x70\x70\x65\x64\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x29\x3b\x0a\x7d\x0a";
const char *shaders_basicobject_v = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x33\x20\x70\x6f\x73\x3b\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x32\x20\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x32\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x0a\x75\x6e\x69\x66\x6f\x72\x6d\x20\x6d\x61\x74\x34\x20\x77\x76\x70\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x09\x67\x6c\x5f\x50\x6f\x73\x69\x74\x69\x6f\x6e\x20\x3d\x20\x77\x76\x70\x20\x2a\x20\x76\x65\x63\x34\x28\x70\x6f\x73\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x09\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x20\x3d\x20\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x7d\x0a";
const char *shaders_particle_v = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x33\x20\x70\x6f\x73\x3b\x0a\x61\x74\x74\x72\x69\x62\x75\x74\x65\x20\x76\x65\x63\x32\x20\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x32\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x0a\x75\x6e\x69\x66\x6f\x72\x6d\x20\x6d\x61\x74\x34\x20\x77\x76\x70\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x09\x67\x6c\x5f\x50\x6f\x73\x69\x74\x69\x6f\x6e\x20\x3d\x20\x77\x76\x70\x20\x2a\x20\x76\x65\x63\x34\x28\x70\x6f\x73\x2c\x20\x31\x2e\x30\x29\x3b\x0a\x09\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x20\x3d\x20\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x7d\x0a";
const char *shaders_particle_f = "\x23\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x32\x30\x0a\x0a\x76\x61\x72\x79\x69\x6e\x67\x20\x76\x65\x63\x32\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x3b\x0a\x75\x6e\x69\x66\x6f\x72\x6d\x20\x73\x61\x6d\x70\x6c\x65\x72\x32\x44\x20\x74\x65\x78\x3b\x0a\x0a\x76\x6f\x69\x64\x20\x6d\x61\x69\x6e\x28\x76\x6f\x69\x64\x29\x0a\x7b\x0a\x20\x20\x20\x20\x76\x65\x63\x32\x20\x66\x6c\x69\x70\x70\x65\x64\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x20\x3d\x20\x76\x65\x63\x32\x28\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x2e\x78\x2c\x20\x66\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x2e\x79\x29\x3b\x0a\x20\x20\x20\x20\x67\x6c\x5f\x46\x72\x61\x67\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x74\x65\x78\x74\x75\x72\x65\x32\x44\x28\x74\x65\x78\x2c\x20\x66\x6c\x69\x70\x70\x65\x64\x5f\x74\x65\x78\x63\x6f\x6f\x72\x64\x29\x3b\x0a\x7d\x0a";
