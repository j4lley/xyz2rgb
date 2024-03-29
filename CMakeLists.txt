#	Copyright (c) 2018, J.A. Iglesias-Guitian <jalley@cvc.uab.es>
#	All rights reserved.
#
#	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#	- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#	- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#	- Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
#	
#	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 2.8)

PROJECT(xyz2rgb)

### Set Build Type ###
SET(CMAKE_BUILD_TYPE "RelWithDebInfo")

# Module Path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

# Find FreeImage
find_package(FreeImage)

#FIND_PACKAGE(CUDA)

# Supported streaming architectures
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_10,code=sm_10;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_10,code=compute_10;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_11,code=sm_11;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_11,code=compute_11;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_12,code=sm_12;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_12,code=compute_12;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_13,code=sm_13;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_13,code=compute_13;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_20,code=sm_20;${CUDA_NVCC_FLAGS}")
# SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_20,code=compute_20;${CUDA_NVCC_FLAGS}")
#SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_60,code=sm_60;${CUDA_NVCC_FLAGS}")
#SET(CUDA_NVCC_FLAGS "-gencode=arch=compute_60,code=compute_60;${CUDA_NVCC_FLAGS}")


# Enable the export of symbols
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_EXPORTING")

# Use the include path and library for Qt that is used by VTK.
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CUDA_SDK_ROOT_DIR}/common/inc
	${CUDA_TOOLKIT_INCLUDE}
	${FREEIMAGE_INCLUDE_DIR}
)

# Set your files and resources here  
SET(xyz2rgb_sources 
	# Main
	xyz2rgb.cpp 
)

SET(xyz2rgb_headers
)

# CUDA sources
#SET(CudaSources
#	CudaUtilities.h
#	CudaUtilities.cpp
#)

# Make the CUDA group
#SOURCE_GROUP("Cuda" FILES ${CudaSources})

IF(WIN32)
	SET(GUI_TYPE WIN32)
ENDIF(WIN32)

# Create executable
#CUDA_ADD_EXECUTABLE(xyz2rgb)
ADD_EXECUTABLE(xyz2rgb ${xyz2rgb_sources})

TARGET_LINK_LIBRARIES(xyz2rgb
  ${FREEIMAGE_LIBRARY}
)

### CUDA dependencies ###
#SET(CudaDlls ${CUDA_TOOLKIT_ROOT_DIR}/bin/cudart32_40_17.dll)
#INSTALL_FILES(/bin FILES ${CudaDlls})

