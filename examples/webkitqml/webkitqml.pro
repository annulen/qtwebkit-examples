TEMPLATE = subdirs
SUBDIRS += shared \
    flickrview \
    youtubeview

!mac:SUBDIRS += browserwindow
