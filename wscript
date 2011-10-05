import Options
from os import unlink, symlink, popen
from os.path import exists 

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "arkleseizure"
  obj.source = "arkleseizure.cpp"
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE"]
  obj.includes = "/usr/include/openbabel-2.0"
  obj.linkflags = ['-lopenbabel']

def shutdown():
  if Options.commands['clean']:
    if exists('arkleseizure.node'): unlink('arkleseizure.node')
  else:
    if exists('build/default/arkleseizure.node') and not exists('arkleseizure.node'):
      symlink('build/default/arkleseizure.node', 'arkleseizure.node')

