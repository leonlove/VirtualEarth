#pragma once

#include    "CELLPlatform.hpp"
#include    "CELLObject.hpp"

#if CELL_PLATFORM == CELL_PLATFORM_WIN32

namespace   CELL
{
    class   CELLThread :public CELLObject
    {
    public:
        DWORD               _threadId;
        HANDLE              _thread;
    protected:
       
        /**
        *   �߳���ں���
        */
        static  unsigned long    __stdcall threadEnter(void* pVoid)
        {
            CELLThread* pThis   =   (CELLThread*)pVoid;
            if (pThis)
            {
                pThis->onCreate();
                pThis->onRun();
                pThis->onDestroy();
            }
            return  0;
        }
    public:
        CELLThread()
        {
            _thread     =   0;
        }
        virtual ~CELLThread()
        {
            join();
        }

        DWORD   threadId() const
        {
            return  _threadId;
        }

        bool    isRun() const
        {
            return  _thread != 0;
        }
        /**
        *   �������֪ͨ����
        */
        virtual bool    onCreate()
        {
            return  false;
        }
        /**
        *   �߳�ִ�к���
        */
        virtual bool    onRun()
        {
            return  false;
        }

        /**
        *   ��������
        */
        virtual bool    onDestroy()
        {
            return  false;
        }
    
        /**
        *   �����̺߳���
        */
        virtual bool    start()
        {
            if (_thread != 0)
            {
                return  false;
            }
            else
            {
                _thread     =   CreateThread(0,0,&CELLThread::threadEnter,this,HIGH_PRIORITY_CLASS,&_threadId);
                return  true;
            }
        }
        /**
        *   �ȴ��˳�����
        */
        virtual void    join()
        {
            if (_thread)
            {
                WaitForSingleObject(_thread,0xFFFFFFFF);
                CloseHandle(_thread);
                _thread     =   0;
            }
        }
        /**
        *   �ر�
        */
        virtual void    close()
        {
            CloseHandle(_thread);
            _thread     =   0;
        }
    };
}

#elif CELL_PLATFORM == CELL_PLATFORM_LINUX

namespace   CELL
{
    class   CELLThread :public CELLObject
    {
    protected:
        pthread_t   _thread;
    protected:

        /**
        *   �߳���ں���
        */
        static  void*    threadEnter(void* pVoid)
        {
            CELLThread* pThis   =   (CELLThread*)pVoid;
            if (pThis)
            {
                pThis->onCreate();
                pThis->onRun();
                pThis->onDestroy();
            }
            return  0;
        }
    public:
        CELLThread()
        {
            _thread     =   0;
        }
        virtual ~CELLThread()
        {
            join();
        }

        size_t   threadId() const
        {
            return  (size_t)_thread;
        }

        bool    isRun() const
        {
            return  _thread != 0;
        }

        /**
        *   �����̺߳���
        */
        virtual bool    start()
        {
            if (_thread != 0)
            {
                return  false;
            }
            else
            {
                pthread_attr_t  attr;
                pthread_attr_init(&attr);
                pthread_attr_setstacksize(&attr, 1024 * 1024);
                pthread_create(&_thread,&attr,&CELLThread::threadEnter,this);
                return  true;
            }
        }
        /**
        *   �ȴ��˳�����
        */
        virtual void    join()
        {
            if (_thread)
            {
                void*   result  =   0;
                if (pthread_join(_thread, &result))
                {
                    throw "cannot join thread";
                }
                pthread_detach(_thread);
                _thread     =   0;
            }
        }
        /**
        *   �ر�
        */
        virtual void    close()
        {
            if(_thread)
            {
                pthread_detach(_thread);
                _thread     =   0;
            }
        }
    protected:
        /**
        *   �������֪ͨ����
        */
        virtual bool    onCreate()
        {
            return  false;
        }
        /**
        *   �߳�ִ�к���
        */
        virtual bool    onRun()
        {
            return  false;
        }

        /**
        *   ��������
        */
        virtual bool    onDestroy()
        {
            return  false;
        }
    };
}
#endif
