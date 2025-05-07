#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=US.c irDetect.c servo.c moteur.c comI2C.c bat.c main.c boussole.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/US.p1 ${OBJECTDIR}/irDetect.p1 ${OBJECTDIR}/servo.p1 ${OBJECTDIR}/moteur.p1 ${OBJECTDIR}/comI2C.p1 ${OBJECTDIR}/bat.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/boussole.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/US.p1.d ${OBJECTDIR}/irDetect.p1.d ${OBJECTDIR}/servo.p1.d ${OBJECTDIR}/moteur.p1.d ${OBJECTDIR}/comI2C.p1.d ${OBJECTDIR}/bat.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/boussole.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/US.p1 ${OBJECTDIR}/irDetect.p1 ${OBJECTDIR}/servo.p1 ${OBJECTDIR}/moteur.p1 ${OBJECTDIR}/comI2C.p1 ${OBJECTDIR}/bat.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/boussole.p1

# Source Files
SOURCEFILES=US.c irDetect.c servo.c moteur.c comI2C.c bat.c main.c boussole.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/US.p1: US.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/US.p1.d 
	@${RM} ${OBJECTDIR}/US.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/US.p1 US.c 
	@-${MV} ${OBJECTDIR}/US.d ${OBJECTDIR}/US.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/US.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/irDetect.p1: irDetect.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/irDetect.p1.d 
	@${RM} ${OBJECTDIR}/irDetect.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/irDetect.p1 irDetect.c 
	@-${MV} ${OBJECTDIR}/irDetect.d ${OBJECTDIR}/irDetect.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/irDetect.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/servo.p1: servo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.p1.d 
	@${RM} ${OBJECTDIR}/servo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/servo.p1 servo.c 
	@-${MV} ${OBJECTDIR}/servo.d ${OBJECTDIR}/servo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/servo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/moteur.p1: moteur.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/moteur.p1.d 
	@${RM} ${OBJECTDIR}/moteur.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/moteur.p1 moteur.c 
	@-${MV} ${OBJECTDIR}/moteur.d ${OBJECTDIR}/moteur.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/moteur.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/comI2C.p1: comI2C.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/comI2C.p1.d 
	@${RM} ${OBJECTDIR}/comI2C.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/comI2C.p1 comI2C.c 
	@-${MV} ${OBJECTDIR}/comI2C.d ${OBJECTDIR}/comI2C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/comI2C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bat.p1: bat.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bat.p1.d 
	@${RM} ${OBJECTDIR}/bat.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bat.p1 bat.c 
	@-${MV} ${OBJECTDIR}/bat.d ${OBJECTDIR}/bat.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bat.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/boussole.p1: boussole.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boussole.p1.d 
	@${RM} ${OBJECTDIR}/boussole.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/boussole.p1 boussole.c 
	@-${MV} ${OBJECTDIR}/boussole.d ${OBJECTDIR}/boussole.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/boussole.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/US.p1: US.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/US.p1.d 
	@${RM} ${OBJECTDIR}/US.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/US.p1 US.c 
	@-${MV} ${OBJECTDIR}/US.d ${OBJECTDIR}/US.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/US.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/irDetect.p1: irDetect.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/irDetect.p1.d 
	@${RM} ${OBJECTDIR}/irDetect.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/irDetect.p1 irDetect.c 
	@-${MV} ${OBJECTDIR}/irDetect.d ${OBJECTDIR}/irDetect.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/irDetect.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/servo.p1: servo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.p1.d 
	@${RM} ${OBJECTDIR}/servo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/servo.p1 servo.c 
	@-${MV} ${OBJECTDIR}/servo.d ${OBJECTDIR}/servo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/servo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/moteur.p1: moteur.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/moteur.p1.d 
	@${RM} ${OBJECTDIR}/moteur.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/moteur.p1 moteur.c 
	@-${MV} ${OBJECTDIR}/moteur.d ${OBJECTDIR}/moteur.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/moteur.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/comI2C.p1: comI2C.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/comI2C.p1.d 
	@${RM} ${OBJECTDIR}/comI2C.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/comI2C.p1 comI2C.c 
	@-${MV} ${OBJECTDIR}/comI2C.d ${OBJECTDIR}/comI2C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/comI2C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bat.p1: bat.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bat.p1.d 
	@${RM} ${OBJECTDIR}/bat.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bat.p1 bat.c 
	@-${MV} ${OBJECTDIR}/bat.d ${OBJECTDIR}/bat.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bat.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/boussole.p1: boussole.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boussole.p1.d 
	@${RM} ${OBJECTDIR}/boussole.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/boussole.p1 boussole.c 
	@-${MV} ${OBJECTDIR}/boussole.d ${OBJECTDIR}/boussole.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/boussole.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fshort-double -fshort-float -memi=wordwrite -O1 -maddrqual=ignore -xassembler-with-cpp -mwarn=0 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/SErobot_V7.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
