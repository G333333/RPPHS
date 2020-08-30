NAME            := RPPHS

#------------------------------------------------

BUILD          := build
SOURCE         := src/
CXX 		   := arm-vita-eabi-g++

#------------------------------------------------

SOURCES        := $(shell find $(SOURCE) -name '*.cpp')

OBJECTS        := $(addprefix $(BUILD)/,$(SOURCES:%.cpp=%.o))

#-------------------------------------------------

CFLAGS         += -Wall -g -Wl,-q -std=c++14
LDFLAGS 	   := -lvita2d -lsoloud -lpthread -lScePgf_stub -lScePvf_stub -lSceGxm_stub
LDFLAGS 	   += -lSceCtrl_stub -lSceTouch_stub -lSceAppUtil_stub -lSceDisplay_stub
LDFLAGS 	   += -lSceLibKernel_stub -lSceSysmodule_stub -lSceSysmem_stub -lScePower_stub
LDFLAGS 	   += -lSceCommonDialog_stub -lSceRegistryMgr_stub -lSceHid_stub -lfreetype
LDFLAGS 	   += -lfreetype -lpng -ljpeg -lSceAudio_stub -lSceDisplay_stub -lSceIofilemgr_stub
LDFLAGS        += -lSceSysmodule_stub -lSceNet_stub -lSceNetCtl_stub -lSceHttp_stub -lSceSsl_stub
LDFLAGS 	   += -lSceAppMgr_stub -ljansson -lcurl -lssl -lcrypto -lc -lm -lz

#-------------------------------------------------

OUTPUT_BOLD    := `tput bold`
OUTPUT_GREEN   := `tput setaf 2`
OUTPUT_BLUE    := `tput setaf 6`
OUTPUT_NORMAL  := `tput sgr0`

#-------------------------------------------------
all: $(NAME).vpk
#-------------------------------------------------

#-------------------------------------------------
$(NAME).vpk: $(NAME).velf
#-------------------------------------------------
	@echo $(OUTPUT_GREEN)$(OUTPUT_BOLD)Building VPK...$(OUTPUT_NORMAL)
	vita-mksfoex -s TITLE_ID=VGEEDEB01 "RPPHS DEBUG" param.sfo
	cp -f param.sfo sce_sys/param.sfo
	# Comment this if you don't have 7zip
	7z a -tzip $(NAME).vpk -r sce_sys/* images/* sounds/* font/* build/* eboot.bin

#--------------------------------------------------
%.velf: %.elf
#--------------------------------------------------
	cp $< $<.unstripped.elf
	arm-vita-eabi-strip -g $<
	vita-elf-create $< $@
	vita-make-fself -s $@ eboot.bin

#-------------------------------------------------
$(NAME).elf: $(OBJECTS)
#-------------------------------------------------
	@echo Linking...
	@$(CXX) $(CFLAGS) -o $(NAME).elf $(OBJECTS) $(LDFLAGS)
	@echo $(OUTPUT_BOLD)$(OUTPUT_GREEN)Build done.$(OUTPUT_NORMAL)

#-------------------------------------------------
$(BUILD)/%.o: %.cpp
#-------------------------------------------------
	@echo $(OUTPUT_BOLD)- $(subst $(SOURCE)/,,$<)$(OUTPUT_NORMAL)
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -I$(dir $<) -c $< -o $@

#-------------------------------------------------
clean:
#-------------------------------------------------
	@echo $(OUTPUT_BLUE)$(OUTPUT_BOLD)Cleaning...$(OUTPUT_NORMAL)
	@rm -rf $(BUILD) $(NAME).velf $(NAME).elf $(NAME).elf.unstripped.elf eboot.bin param.sfo
