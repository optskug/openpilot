# distutils: language = c++
# cython: c_string_encoding=ascii, language_level=3

import numpy as np
cimport numpy as cnp
from libc.string cimport memcpy
from libc.stdint cimport uintptr_t

from msgq.visionipc.visionipc cimport cl_mem
from msgq.visionipc.visionipc_pyx cimport VisionBuf, CLContext as BaseCLContext
from .commonmodel cimport CL_DEVICE_TYPE_DEFAULT, cl_get_device_id, cl_create_context
from .commonmodel cimport mat3, ModelFrame as cppModelFrame


cdef class CLContext(BaseCLContext):
  def __cinit__(self):
    self.device_id = cl_get_device_id(CL_DEVICE_TYPE_DEFAULT)
    self.context = cl_create_context(self.device_id)

cdef class CLMem:
  @staticmethod
  cdef create(void * cmem):
    mem = CLMem()
    mem.mem = <cl_mem*> cmem
    return mem

  @property
  def mem_address(self):
    return <uintptr_t>(self.mem)

cdef class ModelFrame:
  cdef cppModelFrame * frame

  def __cinit__(self, CLContext context):
    self.frame = new cppModelFrame(context.device_id, context.context)

  def __dealloc__(self):
    del self.frame

  def prepare(self, VisionBuf buf, float[:] projection):
    cdef mat3 cprojection
    memcpy(cprojection.v, &projection[0], 9*sizeof(float))
    cdef cl_mem * data
    data = self.frame.prepare(buf.buf.buf_cl, buf.width, buf.height, buf.stride, buf.uv_offset, cprojection)
    return CLMem.create(data)

  def buffer_from_cl(self, CLMem in_frames):
    cdef unsigned char * data2
    data2 = self.frame.buffer_from_cl(in_frames.mem)
    return np.asarray(<cnp.uint8_t[:self.frame.buf_size]> data2)
