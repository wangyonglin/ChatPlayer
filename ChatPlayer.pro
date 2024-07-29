TEMPLATE = subdirs

SUBDIRS = \
          SherpaNcnnPlayer \
          SherpaOnnxPlayer \
          FFmpegPlayer \
          Bootstrap \
          Sample

# where to find the sub projects - give the folders
Bootstrap.subdir = src/Bootstrap

SherpaNcnnPlayer.subdir = src/SherpaNcnnPlayer
SherpaOnnxPlayer.subdir = src/SherpaOnnxPlayer

FFmpegPlayer.subdir = src/FFmpegPlayer
Sample.subdir  = src/Sample

# what subproject depends on others'
SherpaOnnxPlayer.depends = Bootstrap


# what subproject depends on others'
Sample.depends = SherpaNcnnPlayer
Sample.depends = Bootstrap
Sample.depends = SherpaOnnxPlayer
Sample.depends = FFmpegPlayer

