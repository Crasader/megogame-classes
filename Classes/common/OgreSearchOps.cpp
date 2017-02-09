/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2012 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

// Emulate _findfirst, _findnext on non-Windows platforms


#include "OgreSearchOps.h"
#include <stdio.h>
#include <ctype.h>

/* Win32 directory operations emulation */

struct _find_search_t
{
    char *pattern;
    char *curfn;
    char *directory;
    int dirlen;
    DIR *dirfd;
};
        
intptr_t _findfirst(const char *pattern, struct _finddata_t *data)
{
    _find_search_t *fs = new _find_search_t;
    fs->curfn = NULL;
    fs->pattern = NULL;

    // Separate the mask from directory name
    const char *mask = strrchr (pattern, '/');
    if (mask)
    {
        fs->dirlen = mask - pattern;
        mask++;
        fs->directory = (char *)malloc (fs->dirlen + 1);
        memcpy (fs->directory, pattern, fs->dirlen);
        fs->directory [fs->dirlen] = 0;
    }
    else
    {
        mask = pattern;
        fs->directory = strdup (".");
        fs->dirlen = 1;
    }

    fs->dirfd = opendir (fs->directory);
    if (!fs->dirfd)
    {
        _findclose ((intptr_t)fs);
        return -1;
    }

    /* Hack for "*.*" -> "*' from DOS/Windows */
    if (strcmp (mask, "*.*") == 0)
        mask += 2;
    fs->pattern = strdup (mask);

    /* Get the first entry */
    if (_findnext ((intptr_t)fs, data) < 0)
    {
        _findclose ((intptr_t)fs);
        return -1;
    }

    return (intptr_t)fs;
}

int _findnext(intptr_t id, struct _finddata_t *data)
{
    _find_search_t *fs = (_find_search_t *)id;

    /* Loop until we run out of entries or find the next one */
    dirent *entry=NULL;
    for (;;)
    {
        if (!(entry = readdir (fs->dirfd)))
            return -1;

        /* See if the filename matches our pattern */
        if (fnmatch (fs->pattern, entry->d_name, 0) == 0)
            break;
    }

    if (fs->curfn)
        free (fs->curfn);
    data->name = fs->curfn = strdup (entry->d_name);

    size_t namelen = strlen (entry->d_name);
    char *xfn = new char [fs->dirlen + 1 + namelen + 1];
    sprintf (xfn, "%s/%s", fs->directory, entry->d_name);

    /* stat the file to get if it's a subdir and to find its length */
    struct stat stat_buf;
    if (stat (xfn, &stat_buf))
    {
        // Hmm strange, imitate a zero-length file then
        data->attrib = _A_NORMAL;
        data->size = 0;
    }
    else
    {
        if (S_ISDIR(stat_buf.st_mode))
            data->attrib = _A_SUBDIR;
        else
            /* Default type to a normal file */
            data->attrib = _A_NORMAL;

        data->size = (unsigned long)stat_buf.st_size;
    }

    delete [] xfn;

    /* Files starting with a dot are hidden files in Unix */
    if (data->name [0] == '.')
        data->attrib |= _A_HIDDEN;

    return 0;
}

int _findclose(intptr_t id)
{
    int ret;
    _find_search_t *fs = (_find_search_t *)id;
    
    ret = fs->dirfd ? closedir (fs->dirfd) : 0;
    free (fs->pattern);
    free (fs->directory);
    if (fs->curfn)
        free (fs->curfn);
    delete fs;

    return ret;
}

/*
bool is_absolute_path(const char* path)
{
    return path[0] == '/' || path[0] == '\\';
}

std::string concatenate_path(const std::string & base, const std::string& name)
{
    if (base.empty() || is_absolute_path(name.c_str()))
        return name;
    else
        return base + '/' + name;
}
*/
//-----------------------------------------------------------------------
//在该目录下搜索所有符合的文件
void findFiles(const std::string & thisFolder,const std::string& pattern, bool recursive,
               bool dirs,  std::vector<std::string>* simpleList)
{
    intptr_t lHandle, res;
    struct _finddata_t tagData;
    
    // pattern can contain a directory name, separate it from mask
    size_t pos1 = pattern.rfind ('/');
    size_t pos2 = pattern.rfind ('\\');
    if (pos1 == pattern.npos || ((pos2 != pattern.npos) && (pos1 < pos2)))
        pos1 = pos2;
    std::string directory;
    if (pos1 != pattern.npos)
        directory = pattern.substr (0, pos1 + 1);
    
    std::string full_pattern = thisFolder+'/'+ pattern;
    
    lHandle = _findfirst(full_pattern.c_str(), &tagData);
    res = 0;
    while (lHandle != -1 && res != -1)
    {
        if ((dirs == ((tagData.attrib & _A_SUBDIR) != 0)) &&
            (  (tagData.attrib & _A_HIDDEN) == 0 ) &&
            (!dirs ))
        {
            if (simpleList)
            {
                simpleList->push_back(directory + tagData.name);
            }
            
        }
        res = _findnext( lHandle, &tagData );
    }
    // Close if we found any files
    if(lHandle != -1)
        _findclose(lHandle);
    
    // Now find directories
    if (recursive)
    {
        std::string base_dir = thisFolder;
        if (!directory.empty ())
        {
            base_dir = thisFolder+'/'+ directory;
            // Remove the last '/'
            base_dir.erase (base_dir.length () - 1);
        }
        base_dir.append ("/*");
        
        // Remove directory name from pattern
        std::string mask ("/");
        if (pos1 != pattern.npos)
            mask.append (pattern.substr (pos1 + 1));
        else
            mask.append (pattern);
        
        lHandle = _findfirst(base_dir.c_str (), &tagData);
        res = 0;
        while (lHandle != -1 && res != -1)
        {
            if ((tagData.attrib & _A_SUBDIR) &&
                (  (tagData.attrib & _A_HIDDEN) == 0 ) )
            {
                // recurse
                base_dir = directory;
                base_dir.append (tagData.name).append (mask);
                findFiles(thisFolder,base_dir, recursive, dirs, simpleList);
            }
            res = _findnext( lHandle, &tagData );
        }
        // Close if we found any files
        if(lHandle != -1)
            _findclose(lHandle);
    }
}


