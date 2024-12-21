

















/*#include <EngineCore/Engine.hpp>

namespace EngineCore {

    Engine::Engine()
        : m_window(nullptr), instance(VK_NULL_HANDLE), physicalDevice(VK_NULL_HANDLE),
        device(VK_NULL_HANDLE), graphicsQueue(VK_NULL_HANDLE), surface(VK_NULL_HANDLE),
        renderPass(VK_NULL_HANDLE), commandPool(VK_NULL_HANDLE), commandBuffer(VK_NULL_HANDLE),
        imguiDescriptorPool(VK_NULL_HANDLE) {
    }

    Engine::~Engine() {}

    void Engine::Initialize() {
        initWindow();
        initVulkan();
        initImGui();
    }

    void Engine::Run() {
        mainLoop();
        Cleanup();
    }

    void Engine::Cleanup() {
        if (surface != VK_NULL_HANDLE) {
            vkDestroySurfaceKHR(instance, surface, nullptr);
        }

        if (device != VK_NULL_HANDLE) {
            vkDestroyDevice(device, nullptr);
        }

        if (instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
        }

        if (m_window) {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }


    void Engine::renderImGui() {
        ImGui::Begin("Hello, Vulkan!");
        ImGui::Text("Welcome to the Vulkan ImGui demo!");
        ImGui::End();
    }


    void Engine::initWindow() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW!");
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(800, 600, "Vulkan ImGui Example", nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window!");
        }
    }

    void Engine::CreateInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }

        // Створення поверхні
        if (glfwCreateWindowSurface(instance, m_window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface!");
        }
    }

    void Engine::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    bool Engine::isDeviceSuitable(VkPhysicalDevice device) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        bool graphicsQueueFound = false;
        bool presentQueueFound = false;

        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            // Перевірка графічної черги
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphicsQueueFamilyIndex = i;
                graphicsQueueFound = true;
            }

            // Перевірка презентаційної черги
            VkBool32 presentSupport = false;

            if (surface != VK_NULL_HANDLE) { // Перевіряємо, чи surface створена
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            }
            else {
                throw std::runtime_error("Surface is not initialized before calling vkGetPhysicalDeviceSurfaceSupportKHR!");
            }

            if (presentSupport) {
                presentQueueFamilyIndex = i;
                presentQueueFound = true;
            }

            // Завершити пошук, якщо обидві черги знайдено
            if (graphicsQueueFound && presentQueueFound) {
                return true;
            }
        }

        return false;
    }

    void Engine::createLogicalDevice() {
        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Physical device is not selected before creating logical device!");
        }

        float queuePriority = 1.0f;

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        // Графічна черга
        VkDeviceQueueCreateInfo graphicsQueueCreateInfo = {};
        graphicsQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        graphicsQueueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
        graphicsQueueCreateInfo.queueCount = 1;
        graphicsQueueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(graphicsQueueCreateInfo);

        // Презентаційна черга (якщо відрізняється від графічної)
        if (graphicsQueueFamilyIndex != presentQueueFamilyIndex) {
            VkDeviceQueueCreateInfo presentQueueCreateInfo = {};
            presentQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            presentQueueCreateInfo.queueFamilyIndex = presentQueueFamilyIndex;
            presentQueueCreateInfo.queueCount = 1;
            presentQueueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(presentQueueCreateInfo);
        }

        // Розширення для SwapChain
        const char* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.enabledExtensionCount = 1;
        createInfo.ppEnabledExtensionNames = deviceExtensions;

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create logical device!");
        }

        // Отримання черг
        vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);
        vkGetDeviceQueue(device, presentQueueFamilyIndex, 0, &presentQueue);
    }

    void Engine::createDescriptorPool() {
        VkDescriptorPoolSize poolSizes[] = {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 1000 * static_cast<uint32_t>(std::size(poolSizes));
        poolInfo.poolSizeCount = static_cast<uint32_t>(std::size(poolSizes));
        poolInfo.pPoolSizes = poolSizes;

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &imguiDescriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create descriptor pool!");
        }
    }

    void Engine::createCommandPool() {
        // Визначення індексу черги для графіки
        uint32_t queueFamilyIndex = 0;

        // Знайти індекс черги, яка підтримує графічні операції
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                queueFamilyIndex = i;
                break;
            }
        }

        // Створення пулу команд
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndex; // Правильний індекс черги

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create command pool!");
        }

        if (commandPool == VK_NULL_HANDLE) {
            throw std::runtime_error("Command pool was not properly created!");
        }
    }


    void Engine::createCommandBuffer() {
        if (device == VK_NULL_HANDLE) {
            throw std::runtime_error("Logical device is not initialized before allocating command buffer!");
        }

        if (commandPool == VK_NULL_HANDLE) {
            throw std::runtime_error("Command pool is not initialized before allocating command buffer!");
        }

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        VkResult result = vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffer!");
        }

        if (commandBuffer == VK_NULL_HANDLE) {
            throw std::runtime_error("Command buffer was not properly allocated!");
        }
    }

    void Engine::createRenderPass() {
        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = VK_FORMAT_B8G8R8A8_SRGB; // Формат кольору
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // Очищення перед рендерингом
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE; // Збереження результату
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // Для презентації

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create render pass!");
        }
    }

    void Engine::createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            VkImageView attachments[] = { swapChainImageViews[i] };

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create framebuffer!");
            }
        }
    }

    void Engine::initVulkan() {
        CreateInstance();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createRenderPass();
        createFramebuffers(); // Виклик після створення RenderPass
        createCommandPool();
        createCommandBuffer();
    }


    void Engine::initImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui_ImplGlfw_InitForVulkan(m_window, true);

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = instance;
        init_info.PhysicalDevice = physicalDevice;
        init_info.Device = device;
        init_info.Queue = graphicsQueue;
        init_info.DescriptorPool = imguiDescriptorPool;
        init_info.MinImageCount = static_cast<uint32_t>(swapChainImages.size()); // Відповідає кількості зображень у SwapChain
        init_info.ImageCount = static_cast<uint32_t>(swapChainImages.size());
        init_info.PipelineCache = VK_NULL_HANDLE;
        init_info.Allocator = nullptr;

        ImGui_ImplVulkan_Init(&init_info, renderPass);

        VkCommandBuffer commandBuffer = beginSingleTimeCommands();
        ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
        endSingleTimeCommands(commandBuffer);
        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    VkCommandBuffer Engine::beginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffer!");
        }

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        return commandBuffer;
    }

    void Engine::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to end command buffer!");
        }

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit command buffer!");
        }

        vkQueueWaitIdle(graphicsQueue);
        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }


    void Engine::cleanupImGui() {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (imguiDescriptorPool != VK_NULL_HANDLE) {
            vkDestroyDescriptorPool(device, imguiDescriptorPool, nullptr);
        }
    }

    void Engine::mainLoop() {
        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();

            // Початок нового кадру ImGui
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Рендеринг вмісту ImGui
            renderImGui();

            // Завершення кадру ImGui
            ImGui::Render();

            // Виконання рендер-проходу
            VkCommandBuffer commandBuffer = beginSingleTimeCommands();

            VkClearValue clearColor = { {{0.1f, 0.1f, 0.1f, 1.0f}} };

            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[currentFrame];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            // Рендеринг ImGui
            if (ImGui::GetDrawData() != nullptr) {
                ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
            }
            else {
                throw std::runtime_error("ImGui::GetDrawData returned nullptr!");
            }

            vkCmdEndRenderPass(commandBuffer);
            endSingleTimeCommands(commandBuffer);

            // Оновлення поточного кадру
            currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
        }
    }

}*/