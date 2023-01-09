#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "cstdmf/bw_namespace.hpp"
#include "cstdmf/bw_string.hpp"


BW_BEGIN_NAMESPACE

/**
 * Subclasses of FileHandler are used for managing pretty much all the files
 * generated by the logs except for the actual log entry / args blob files.
 * Note that each class defines an 'init' method ... those with a first
 * argument called 'path' expect the exact filename of the file to be
 * passed, whereas those whose first argument is 'root' expect the
 * containing directory name to passed; they work out their filename from
 * that path.
 */
class FileHandler
{
public:
	bool init( const char *path, const char *mode );

	// candidate for cleanup. only used in bwlog_reader
	bool isDirty();

	const char *filename() const;

	virtual bool read() = 0;
	virtual long length() = 0;
	bool refresh();

	static const char *join( const char *dir, const char *filename );

protected:
	// Flush should only ever be called by refresh.
	virtual void flush() {}

	BW::string filename_;
	BW::string mode_;

	// candidate for cleanup. should this actually be a long?
	// This is only really tracked in "r" mode
	long length_;

	static char s_pathBuf_[];
};

BW_END_NAMESPACE

#endif // FILE_HANDLER_HPP
