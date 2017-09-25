"""
### JSNIGetVersion
`int JSNIGetVersion(JSNIEnv* env)`

**SUMMARY**

Returns the version of the JSNI.


**PARAMETERS**

None.



**RETURNS**

Returns the version of the JSNI.

sample:
/*! \fn int read(int fd,char *buf,size_t count)
    \brief Read bytes from a file descriptor.
    \param fd The descriptor to read from.
    \param buf The buffer to read into.
    \param count The number of bytes to read.
    \return The test results
*/
"""
import sys
import re

BLOCK_B="/*!"
BLOCK_E="*/"
BLOCK_ALIGN="    "

HEAD3="###"
SUMMARY="SUMMARY"
SUMMARY_SIZE=len(SUMMARY)
ADD_SUMMARY_INDEX=SUMMARY_SIZE + 4
SUB_PARAMETERS_INDEX=5

PARAMETERS="PARAMETERS"
PARAMETERS_SIZE=len(PARAMETERS)
ADD_PARAMETERS_INDEX=PARAMETERS_SIZE + 4
SUB_RETURNS_INDEX=6

RETURNS="RETURNS"
RETURNS_SIZE=len(RETURNS)
ADD_RETURNS_INDEX=RETURNS_SIZE + 4

ENV_DESCRIPTION="env The JSNI enviroment pointer."

def rm_blank_lines(str):
  #return re.sub("\n\s*\n*", "\n", str)
  while "\n\n" in str:
    str = str.replace("\n\n", "\n")
  return str

def doxy_print_fn(block):
  index_0 = block.find("`")
  index_1 = block.find("`", index_0 + 1)
  print("\\fn"),
  func = block[index_0 + 1:index_1]
  print(func)
  return func

def doxy_print_brief(block):
  index_0 = block.find(SUMMARY)
  index_1 = block.find(PARAMETERS)
  print(BLOCK_ALIGN + "\\brief"),
  print(rm_blank_lines(block[index_0 + ADD_SUMMARY_INDEX:index_1 - SUB_PARAMETERS_INDEX]))

def doxy_trans_params(item):
  if ":" not in item:
    return item
  else:
    index = item.find(":")
    trans_params = item.replace(":", "")
    replace_index = index + 1
    params_prologue = BLOCK_ALIGN + "\param "

    return params_prologue\
           + trans_params[:replace_index]\
           + trans_params[replace_index].upper()\
           + trans_params[replace_index + 1:]

def doxy_print_params(block):
  index_0 = block.find(PARAMETERS)
  index_1 = block.find(RETURNS)
  str_pa = rm_blank_lines(block[index_0 + ADD_PARAMETERS_INDEX:index_1 - SUB_RETURNS_INDEX])
  list_copy = []
  list_copy.append(BLOCK_ALIGN + "\param " + ENV_DESCRIPTION)
  # has parameter description in it.
  if ":" in str_pa:
    list_pa = str_pa.split("\n")
    l = len(list_pa)
    for x in xrange(0, l):
      trans_params = doxy_trans_params(list_pa[x])
      if "\param" in trans_params:
        list_copy.append(trans_params)
      else:
        assert(x > 0)
        list_copy[x - 1] = list_copy[x - 1] + " " + trans_params
  for i in list_copy:
    print(i)


def doxy_print_return(block):
  index_0 = block.find(RETURNS)
  print(BLOCK_ALIGN + "\\return"),
  result = rm_blank_lines(block[index_0 + ADD_RETURNS_INDEX:])
  print(result.strip())


def doxy_block(block):
  print(BLOCK_B),
  func = doxy_print_fn(block)
  doxy_print_brief(block)
  doxy_print_params(block)
  doxy_print_return(block)
  print(BLOCK_E)
  print(func) + ";\n"

def doxy_blocks(blocks):
  for block in blocks:
    doxy_block(block)

def doxy(file_in):
  with open(file_in, 'r') as f:
    content = f.read()
    blocks = content.split(HEAD3)
    blocks_copy = blocks[1:]
    doxy_blocks(blocks_copy)

def main():
  file_in = sys.argv[1]
  doxy(file_in)

if __name__ == '__main__':
  main()