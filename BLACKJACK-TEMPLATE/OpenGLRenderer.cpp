#include "pch.h"
#include "OpenGLRenderer.h"
#include "SceneManager.h"

OpenGLRenderer::OpenGLRenderer(int d, Camera* c)
{
	glContext = SDL_GL_CreateContext(Window::getSDLWindow());

	if (glContext)
	{
		LOG_INFO("OpenGL context created...");
		int width, height;

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			LOG_INFO("Could not initializw glew...");
		}

		SDL_GetWindowSize(Window::getSDLWindow(), &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		LOG_INFO("OpenGL context could not be created...");
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(Window::getSDLWindow());
		SDL_Quit();
		return;
	}

	driver = d;
	flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
	renderer = SDL_CreateRenderer(Window::getSDLWindow(), driver, flags);

	if (renderer != 0)
	{
		LOG_INFO("Renderer created...");

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		camera = c;
	}
	else
		LOG_INFO("Renderer was not created...");
}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_GL_DeleteContext(glContext);
}

void OpenGLRenderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SceneManager::getInstance()->render();

	SDL_GL_SwapWindow(Window::getSDLWindow());
}

SDL_GLContext OpenGLRenderer::getGLContext()
{
	return glContext;
}

SDL_GLContext OpenGLRenderer::glContext;