#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define STB_IMAGE_IMPLEMENTATION

#include "GraphicsManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include "sokol_gfx.h"
#include "stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

namespace bingusengine {
    namespace {
        struct Uniforms {
            mat4 projection;
            mat4 transform;
        };
    }

    struct B_Image {
        sg_image image;
        int width;
        int height;
    };

    struct GraphicsManager::impl {
        int window_width;
        int window_height;
        Engine* e = nullptr;

        GLFWwindow* window;

        sg_pipeline pipeline{};
        sg_bindings bindings{};
        sg_pass_action pass_action{};

        std::unordered_map<string, B_Image> images;
    };

    void GraphicsManager::Init(Engine* e, int win_w, int win_h){
        
        /* Initialize Class members.
         */
        priv->window_width = win_w;
        priv->window_height = win_h;
        priv->e = e;

        /* Set up GLFW and open a window.
         */
        glfwInit();
        // We'll use sokol_gfx's OpenGL backend
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        priv->window = glfwCreateWindow( priv->window_width, priv->window_height, "Bingus Engine", /*fullscreen?*/false ? glfwGetPrimaryMonitor() : 0, 0 );
        glfwSetWindowAspectRatio( priv->window, priv->window_width, priv->window_height );
        if( !priv->window )
        {
            std::cerr << "Failed to create a window." << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent( priv->window );
        glfwSwapInterval(1);

        /* Set up Sokol and define a shader program.
         */
        sg_setup(sg_desc{});
        sg_buffer_desc buffer_desc{};
        buffer_desc.data = SG_RANGE(vertices);
        sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

        sg_pipeline_desc pipeline_desc{};
        pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
        pipeline_desc.colors[0].blend.enabled = true;
        pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
        pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

        sg_shader_desc shader_desc{};
        shader_desc.vs.source = R"(
            #version 330
            uniform mat4 projection;
            uniform mat4 transform;
            layout(location=0) in vec2 position;
            layout(location=1) in vec2 texcoords0;
            out vec2 texcoords;
            void main() {
                gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
                texcoords = texcoords0;
            })";

        shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
        // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
        shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
        shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
        shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
        shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

        shader_desc.fs.source = R"(
            #version 330
            uniform sampler2D tex;
            in vec2 texcoords;
            out vec4 frag_color;
            void main() {
                frag_color = texture( tex, texcoords );
                // If we're not drawing back to front, discard very transparent pixels so we
                // don't write to the depth buffer and prevent farther sprites from drawing.
                if( frag_color.a < 0.1 ) discard;
            })";

        shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
        shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

        pipeline_desc.shader = sg_make_shader( shader_desc );
        priv->pipeline = sg_make_pipeline( pipeline_desc );

        priv->pass_action.colors[0].action = SG_ACTION_CLEAR;
        priv->pass_action.colors[0].value = {0., 0., 0., 1.};

        priv->bindings.vertex_buffers[0] = vertex_buffer;
    }

    void GraphicsManager::LoadImage(const string& name, const string& path){
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

        sg_image_desc image_desc{};
        image_desc.width = width;
        image_desc.height = height;
        image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
        image_desc.min_filter = SG_FILTER_LINEAR;
        image_desc.mag_filter = SG_FILTER_LINEAR;
        image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.data.subimage[0][0].ptr = data;
        image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

        sg_image image = sg_make_image(image_desc);

        priv->images[name].image = image;
        priv->images[name].width = width;
        priv->images[name].height = height;

        stbi_image_free(data);
    }

    void GraphicsManager::DestroyImage(const string& name){
        sg_destroy_image(priv->images[name].image);
        priv->images.erase(name);
    }

    void GraphicsManager::Shutdown(){
        glfwTerminate();
        sg_shutdown();
    }

    void GraphicsManager::Draw(){
        glfwGetFramebufferSize(priv->window, &priv->window_width, &priv->window_height);
        sg_begin_default_pass(priv->pass_action, priv->window_width, priv->window_height);
        sg_apply_pipeline(priv->pipeline);

        // make uniforms struct.
        // compute uniforms projections & transform.
        // Start with an identity matrix.
        Uniforms uniforms{};

        priv->e->ecs.ForEach<Sprite>([&](uint64_t entity){
            // Sprite sprite = priv->e->ecs.Get<Sprite>(entity);
            Sprite sprite;

            uniforms.projection = mat4{1};
            // Scale x and y by 1/100.
            uniforms.projection[0][0] = uniforms.projection[1][1] = 1./100.;

            if(priv->window_width < priv->window_height) {
                uniforms.projection[1][1] *= priv->window_width;
                uniforms.projection[1][1] /= priv->window_height;
            } else {
                uniforms.projection[0][0] *= priv->window_height;
                uniforms.projection[0][0] /= priv->window_width;
            }

            uniforms.transform = translate( mat4{1}, vec3( sprite.position, sprite.z ) ) * scale( mat4{1}, -vec3( sprite.scale ) );

            if(priv->images[sprite.name].width < priv->images[sprite.name].height) {
                uniforms.transform = uniforms.transform * scale( mat4{1}, vec3( double(priv->images[sprite.name].width)/priv->images[sprite.name].height, 1.0, 1.0 ) );
            } else {
                uniforms.transform = uniforms.transform * scale( mat4{1}, vec3( 1.0, double(priv->images[sprite.name].height)/priv->images[sprite.name].width, 1.0 ) );
            }

            sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));
            priv->bindings.fs_images[0] = priv->images[sprite.name].image;
            sg_apply_bindings(priv->bindings);
            sg_draw(0, 4, 1);
        });
        

        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(priv->window);
    }

    bool GraphicsManager::ShouldQuit(){
        return glfwWindowShouldClose(priv->window);
    }

    // has to return a void* for now. Gross.
    void* GraphicsManager::window(){
        return priv->window;
    }

    GraphicsManager::GraphicsManager() : priv(std::make_unique<impl>()){}
    GraphicsManager::~GraphicsManager() = default;
}