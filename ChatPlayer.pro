TEMPLATE = subdirs

SUBDIRS = \
          SherpaNcnnPlayer \
          SherpaOnnxPlayer \
          FFmpegPlayer \
          NaturalPlayer \
          Sample

# where to find the sub projects - give the folders
NaturalPlayer.subdir = src/NaturalPlayer

SherpaNcnnPlayer.subdir = src/SherpaNcnnPlayer
SherpaOnnxPlayer.subdir = src/SherpaOnnxPlayer

FFmpegPlayer.subdir = src/FFmpegPlayer
Sample.subdir  = src/Sample

# what subproject depends on others'
SherpaOnnxPlayer.depends = NaturalPlayer


# what subproject depends on others'
Sample.depends = SherpaNcnnPlayer
Sample.depends = NaturalPlayer
Sample.depends = SherpaOnnxPlayer
Sample.depends = FFmpegPlayer

