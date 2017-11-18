#include "pfm.h"

PagedFileManager* PagedFileManager::_pf_manager = 0;

PagedFileManager* PagedFileManager::instance()
{
	if (!_pf_manager)
		_pf_manager = new PagedFileManager();

	return _pf_manager;
}


PagedFileManager::PagedFileManager()
{
}


PagedFileManager::~PagedFileManager()
{
}


RC PagedFileManager::createFile(const string &fileName)
{
	if (fileExists(fileName))
		return -1;
	pFile = fopen(fileName.c_str(), "wb");
	fclose(pFile);
	return 0;
}


RC PagedFileManager::destroyFile(const string &fileName)
{
	if (!fileExists(fileName))
		return -1;
	remove("myfile.txt");
	return 0;
}


RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle)
{
	if (!fileExists(fileName))
		return -1;
	if (fileHandle.handleExists())
		return -1;
	pFile = fopen(fileName.c_str(), "rb+");
	fileHandle.setHandle(pFile);
	return 0;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle)
{
	return -1;
}


FileHandle::FileHandle()
{
	pFile = NULL;
	readPageCounter = 0;
	writePageCounter = 0;
	appendPageCounter = 0;
}


FileHandle::~FileHandle()
{
}


RC FileHandle::readPage(PageNum pageNum, void *data)
{
	if (pageNum >= getNumberOfPages() - 1)
		return -1;
	fseek(pFile, ( pageNum + 1 ) * PAGE_SIZE, SEEK_SET);
	fread(data, PAGE_SIZE, 1, pFile);
	readPageCounter++;
	return 0;
}


RC FileHandle::writePage(PageNum pageNum, const void *data)
{
	if (pageNum >= getNumberOfPages() - 1)
		return -1;
	fseek(pFile, (pageNum + 1) * PAGE_SIZE, SEEK_SET);

	return -1;
}


RC FileHandle::appendPage(const void *data)
{
	return -1;
}


unsigned FileHandle::getNumberOfPages()
{
	return -1;
}


RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount)
{
	return -1;
}

bool PagedFileManager::fileExists(const string &fileName)
{
	pFile = fopen(fileName.c_str(), "rb");
	if (pFile != NULL)
	{
		fclose(pFile);
		return true;
	}
	return false;
}

bool FileHandle::handleExists()
{
	if (pFile != NULL)
		return true;
	return false;
}

RC FileHandle::setHandle(FILE* tempFile)
{
	pFile = tempFile;
	if (getNumberOfPages()==0)
	{
		appendPage();
	}
	else
	{

	}
	return 0;
}

RC FileHandle::updateCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount)
{
	return -1;
}